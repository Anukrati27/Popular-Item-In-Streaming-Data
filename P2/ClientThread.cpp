#include "ClientThread.hpp"
#include "GlobalVars.hpp"

void ClientThread::operator() (string host, int port)
{
    try{

        c = new Client(host, port);
        bool flag = c->connectToServer();
        if (flag == false){
            clientFlag = true;
            return;
        }
        
        c->readDataFromServer();
        if (c != NULL ){
            delete c;
            c = NULL;
        }
        clientFlag = true;
    }
    catch(...){
        cout << "\nError in connecting to client or receiving data from server. Exiting!!!!\n";
        clientFlag = true;
    }
}

ClientThread::~ClientThread(){
    //cout << "\n\n ----DELETING client thread \n " << clientFlag ;
    if (c != NULL)
        delete c;
}


