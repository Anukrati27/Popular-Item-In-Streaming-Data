#ifndef __CLIENT_H_INCLUDED__  
#define __CLIENT_H_INCLUDED__  

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <thread>
#include <iterator>

using namespace std;


class Client{

    private:
        struct sockaddr_in serAddress;
        int sock;
        int port;
        string ipAddress;
    public:
        Client(string host, int port);
        bool connectToServer();
        void readDataFromServer();
        bool checkValidIpAddress();
        //void addDataToMostPopMap(string data);
};

#endif 
