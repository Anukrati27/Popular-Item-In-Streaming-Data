#include "AddDataToMap.hpp"
#include "GlobalVars.hpp"


void AddDataToMap::operator()(){
    while(1){
        try{
            while (addDataList.empty()){
                if (clientFlag == true || interruptFlag == true){
                    computeFlag = true;
                    cout << "\nConnection to server lost. Exiting Computation Thread\n";
                    return;
                }
                usleep(1000);
            }
            if (interruptFlag == true){
                computeFlag = true;
                cout << "\nExiting Computation Thread due to interrupt\n";
                break;
            }
            mtx.lock();
           
            string dataInString = addDataList.front();
            addDataList.pop();
            mtx.unlock();
            
            vector<string> data = splitString(dataInString);
            vector<string>::iterator it = data.begin();
            string::size_type pos = 0;
            string temp;
    
            for ( ; it != data.end(); ++it){
                temp = *it;
                if (temp == "")
                    continue;
                pos = temp.find(' ');

                double date = stod(temp.substr(0, pos));
                string key = temp.substr(pos+1, temp.length());
                addAndUpdateMapData(key, date);
            }
        }
        catch(...){
            cout << "\n\nCorrupted data received from server. Skipping the set of data and continuing.\n";
        }
    }
}

void AddDataToMap::addAndUpdateMapData( string key, double date){
    map<string, vector<double>>::iterator it = mostPopItem.begin();
    vector<string> keyMap;
    for(; it != mostPopItem.end(); ++it){
        (it->second)[0] = ((it->second)[0])*decayConst;
        
        if((it->second)[0] <= 0.5 && it->first != key)
            keyMap.push_back(it->first);
    }

    vector<string>::iterator it1 = keyMap.begin();
    for ( ; it1 != keyMap.end(); ++it1){
        mostPopItem.erase(*it1);
    }
   
    if (mostPopItem.count(key) == 0){
        vector< double> vec { 1.0, date };
        mostPopItem.insert( pair<string, vector<double> >(key, vec) );
        currentTimestamp = date;
    }
    else{
        mostPopItem[key][0] = 1.0 + mostPopItem[key][0];
        mostPopItem[key][1] = date;
        currentTimestamp = date;
    }
}

vector<string> AddDataToMap::splitString(const string& str)
{
    vector<string> returnVec;

    string::size_type pos = 0;
    string::size_type prev = 0;
    while ((pos = str.find('\n', prev)) != string::npos){
        returnVec.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }
    if (prev != string::npos)
        returnVec.push_back(str.substr(prev));
    return returnVec;
}


