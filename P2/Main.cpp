#include <iostream>
#include <thread>
#include <string>
#include <signal.h>
#include <unistd.h>
#include "GlobalVars.hpp"
#include "ConsoleThread.hpp"
#include "ClientThread.hpp"
#include "AddDataToMap.hpp"

using namespace std;


bool interruptFlag;
bool clientFlag;
bool computeFlag;
double decayConst;
mutex mtx;
map<string, vector<double> > mostPopItem;
queue<string> addDataList;
double currentTimestamp;

void exitOnInterrupt(int sig){
    interruptFlag = true;
    while(clientFlag != true || computeFlag != true){
        usleep(100000);
    }
    cout << "\nExiting Main Thread. Interrupt Signal Received.\n";
    exit(0);
}


int main(int argc, char** argv) {
  
    try{
        interruptFlag = false;
        clientFlag = false;
        computeFlag = false;
        signal(SIGINT, exitOnInterrupt);

        if (argc != 2){
            cout << "\n\nInvalid number of arguments Provided.\nPlease enter input in form './P2 portNumber'.\n Exiting!!!!\n\n";
            exit(1);
        }

        string host = "localhost";
        int port = atoi(argv[1]);
        cout << "\nEnter decay constant -> ";
        cin >> decayConst;
        if (! cin.good()){
            cout << "\nInvalid decay constant provided. Exiting!!!!\n";
            exit(0);
        }       
        //decayConst = stod(argv[2]);
        thread computeThread( (AddDataToMap()) );
        thread clientThread( (ClientThread()) ,host, port);
        thread consoleThread( (ConsoleThread()) );

        while( clientFlag == false){
            usleep(100);
        }
        while(computeFlag == false){
            usleep(100);
        }
        //consoleThread.join();
        cout << "\nExiting Application!!!\n\n";
        exit(0);
    }
    catch(...){
        cout << "\nError in Application. Exiting\n\n";
        exit(0);
    }  
}

