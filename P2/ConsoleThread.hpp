#ifndef __CONSOLETHREAD_H_INCLUDED__
#define __CONSOLETHREAD_H_INCLUDED__


#include <iostream>
#include <string>
#include <algorithm>
#include <unistd.h>

using namespace std;


class ConsoleThread{

    string query;
    void removeSpaces();
    string computeTheMostPopularItemId();
public:
    void operator()();

};

#endif


