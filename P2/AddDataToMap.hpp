#ifndef __ADDDATATOMAP_H_INCLUDED__
#define __ADDDATATOMAP_H_INCLUDED__


#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
using namespace std;

class AddDataToMap{

    vector<string> splitString(const string& str);
    void addAndUpdateMapData( string key, double date);
public:
    void operator()();
    //void addData(string dataInString);
};

#endif
