#include <unistd.h>
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>
#include <signal.h>
#include <sstream>
#include <libwebsockets.h>
#include <set>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "header.h"


////////////////////////////////////////////////////////////////////////////////////////
#define MYFIFO "my_fifo" 
#define MYFIFO2 "my_fifo2"

int loggato = 0;
int N = 0;

using namespace std;

typedef struct WSContent{
  int port;
  const char *interface;

}WSContent;

static int callback_http(
    struct lws *wsi,
    enum lws_callback_reasons reason,
    void *user,
    void *in,
    size_t len
) {
  switch (reason) {

    case LWS_CALLBACK_ESTABLISHED:
      printf("connection established\n");
      break;

    case LWS_CALLBACK_RECEIVE: {

      break;
    }
    default:
      break;
  }

  return 0;
}

static int callback_dumb_increment( //struct libwebsocket_context * this_context,
                                  struct lws *wsi,
                                  enum lws_callback_reasons reason,
                                  void *user, void *in, size_t len) {

  switch (reason) {
  case LWS_CALLBACK_ESTABLISHED:
    printf("connection established\n");

    break;

  case LWS_CALLBACK_RECEIVE: {

      //GESTISCO LA RISPOSTA DA PARTE DELL'UTENTE
      char *buf = (char*) malloc((sizeof(char)*len)+1);
      strncpy(buf,(char*)in,len);
      float *coordinate;
      int size;

      //VERIFICO SE LA STRINGA È RELATIVA AL BOTTONE "CHIAMA ROBOT" O MENO
      if (len>13) {
        std::string s = (string)buf;
        std::string token = s.substr(0, s.find(":")); // token is stanza           
        size = token.length();
        strcpy(buf, token.c_str());
        buf[size] = '\0';
        cout << "chiamata" << " --> " << buf << endl;
        lws_write(wsi, (unsigned char*) buf, size, LWS_WRITE_TEXT);
      }
      else {
        buf[len] = '\0';
        size = strlen(buf);
      }

      //COMUNICAZIONE TRAMITE NAMED PIPE PER LO SCAMBIO DEL MESSAGGIO (INVIO COORDINATE AL ROBOT)
      int i;
      int fd = open(MYFIFO,O_WRONLY);
      if (!fd) {
        cerr << "Errore apertura in scrittura della fifo" << endl;
        return EXIT_FAILURE;
      }

      //prendo le coordinate da inviare al robot
      if (loggato<N) {
        stanzaLog((string)buf); 
        lws_write(wsi, (unsigned char*) buf, size, LWS_WRITE_TEXT);
        loggato++;
      }
      else {
        coordinate = getStanza((string)buf);
        if (coordinate[3]==1) {
          cout << "INVIO COORDINATE AL ROBOT: " << coordinate[0] << " "
          << coordinate[1] << " " << coordinate[2] << " " << endl;
          for (i=0;i<3;i++) {
            if(write(fd,&coordinate[i],sizeof(float))==-1) {
              cerr << "Errore di scrittura nella fifo" << endl;
              return EXIT_FAILURE;
            }
          }
          lws_write(wsi, (unsigned char*) buf, size, LWS_WRITE_TEXT);
          count++; 
        }
        else {
          string h = "help";
          char *help = (char*) malloc((sizeof(char)*11));
          strcpy(help, h.c_str());
          size = strlen(help);
          help[size] = '\0';
          size = strlen(help);
          lws_write(wsi, (unsigned char*) help, size, LWS_WRITE_TEXT);
        }
      }

      // Cotrollo consegna effettuata
      if (count==2) {
        int* consegna = (int*)malloc(sizeof(int));
        int fd2 = open(MYFIFO2,O_RDONLY);
        if (!fd2) {
          cerr << "Errore apertura in lettura della fifo" << endl;
          return EXIT_FAILURE;
        }
        if(read(fd2,&consegna[0], sizeof(int))==-1) {
            cerr << "Errore di lettura nella fifo" << endl;
            return EXIT_FAILURE;
        }
        close(fd2);
        if (consegna[0]==1) {
          string c = "consegnato";
          char *consegnato = (char*) malloc((sizeof(char)*11));
          strcpy(consegnato, c.c_str());
          size = strlen(consegnato);
          consegnato[size] = '\0';
          size = strlen(consegnato);
          lws_write(wsi, (unsigned char*) consegnato, size, LWS_WRITE_TEXT);
        }
      }
    
      close(fd);
        

    }
    break;


  default:
    break;
  }

  return 0;
}



int webServerCreate(int n){
  N=n;
  int port = 9002;
  int opts = 0;
  const char *interface = NULL;
  struct lws_context *context;
  struct lws_context_creation_info info;

  //INIZIALIZZO STANZE VUOTE
  resetLog();

  //CREZIONE FIFO
  int res;
  unlink(MYFIFO);
  res = mkfifo(MYFIFO,0666);
  if (res==-1) {
    cerr << "Errore creazione fifo" << endl;
    return EXIT_FAILURE;
  }

  memset(&info, 0, sizeof info);

  struct lws_protocols protocols[] = {
    // first protocol must always be HTTP handler 
    {
      .name="http-only",   // name
      .callback=callback_http, // callback
      .per_session_data_size=0,              // per_session_data_size
      .rx_buffer_size=0
    },
    {
      .name = "web-protocol", // protocol name 
      .callback = callback_dumb_increment,   // callback
      .per_session_data_size=0,                          // we don't use any per session data
      .rx_buffer_size=0
    },
    {
      .name=NULL,
        .callback=NULL,
        .per_session_data_size=0,   // End of list 
        .rx_buffer_size=0
    }
  };

  info.port = port;
  info.iface = interface;
  info.protocols = protocols;
  info.ssl_cert_filepath = NULL;
  info.ssl_private_key_filepath = NULL;
  info.gid = -1;
  info.uid = -1;
  info.options = opts;



  // create libwebsocket context representing this server
  context = lws_create_context(&info);

  if (context == NULL) {
    fprintf(stderr, "libwebsocket init failed\n");
    return -1;
  }

  printf("starting server...\n");

  // infinite loop, to end this server send SIGTERM. (CTRL+C)
  while (1) {
    lws_service(context, 50);
    // libwebsocket_service will process all waiting events with
    // their callback functions and then wait 50 ms.
    // (this is a single threaded web server and this will keep our
    // server from generating load while there are not
    // requests to process)
  }

  lws_context_destroy(context);

  return 0;

}
