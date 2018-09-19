#ifndef __CLIENTTHREAD_H_INCLUDED__
#define __CLIENTTHREAD_H_INCLUDED__


#include <iostream>
#include <string>
#include "Client.hpp"
#include <signal.h>


using namespace std;


class ClientThread{

    Client *c;

public:
    //bool operator()(string host, int port);
    ~ClientThread();
    void operator() (string host, int port);
};

#endif
