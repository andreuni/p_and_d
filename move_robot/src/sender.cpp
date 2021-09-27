
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "ros/ros.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <move_robot/NewGoal.h>

#define MYFIFO "Server/my_fifo" 
using namespace std;

move_robot::NewGoal msg;
int fd;

int main(int argc, char**argv) {
    
    ros::init(argc,argv,"send");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<move_robot::NewGoal>("NewGoal",1000);


    //APERTURA FIFO CON DENTRO COORDINATE
    int fd = open(MYFIFO, O_RDONLY);
    if (fd==-1) {
        cerr << "Errore apertura in lettura della fifo" << endl;
        return EXIT_FAILURE;
    }
    int i;
    int count=0;
    while(ros::ok()) {

        //LETTURA COORDINATE DALLA FIFO
        float* coordinate = (float*)malloc(sizeof(float)*3);
        for (i=0;i<3;i++) {
            if(read(fd,&coordinate[i], sizeof(float))==-1) {
                cerr << "Errore di lettura nella fifo" << endl;
                return EXIT_FAILURE;
            }
        }
        //SETTO LE COORDINATE NEL MESSAGGIO 
        
        msg.x =(float) coordinate[0];
        msg.y = (float) coordinate[1];
        msg.theta = (float) coordinate[2];

        // CONTROLLO DELLA VALIDITÀ DELLE COORDINATE
       
        
        if (coordinate[0]>1 && coordinate[1]>1 ) {
            cout  << "COORDINATE: " << msg.x << " " << msg.y << " " << msg.theta << endl; 
            cout << "PUBBLICAZIONE GOAL..." << endl;
            for (i=0;i<2;i++) { //pubblico due volte il messaggio per essere sicuro che il move lo abbia ricevuto
                pub.publish(msg); 
                sleep(5); 
            }
        }
        

        ros::spinOnce();
        sleep(5);

        
    }
    
    close(fd);

    return EXIT_SUCCESS;
    
}
