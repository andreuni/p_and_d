#include <iostream>
#include <fstream>
#include "header.h"
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[]){

  if (argc<2) {
    cerr << "Inserire il numero di utenti che possono accedere all'edificio" << endl;
    return EXIT_FAILURE;
  }
  int n = atoi(argv[1]);
  cout << "NUMERO UTENTI: " << n << " \n" << endl;
  cout << "\nLETTURA DELLE STANZE DAL DATABASE\n" << endl;
  //if (reader_table() != 1) {
   //   cerr << "Errore nella lettura dal database" << endl;
    //  return EXIT_FAILURE;
   // }
  cout << "\nAVVIO CONNESSIONE SULLA PORTA 9002\n" << endl;
  if(webServerCreate(n) == -1){
    cerr << "Errore nella socket\n" << endl;
    return EXIT_FAILURE;
  };

  
  return EXIT_SUCCESS;
}

