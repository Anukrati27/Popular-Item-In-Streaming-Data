#include "ConsoleThread.hpp"
#include "GlobalVars.hpp"

void ConsoleThread::operator()()
{
    usleep(10000);
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    while(1){
        try{ 
            cout << "\n\nEnter Query --> \n";
            getline (cin, query);
            
            if(query == "abcd"){
                map<string, vector<double>>::iterator it = mostPopItem.begin();

                for(; it != mostPopItem.end(); ++it){
                    cout << "\nkey->"<<it->first<<" value-->"<<(it->second)[1]<<" decay-->" << (it->second)[0]<<"\n";
                }
            }

            if (interruptFlag == true){
                cout << "\nExiting Console Thread.\n";
                break;
            }
            transform(query.begin(), query.end(), query.begin(), ::tolower);        
            replace(query.begin(), query.end(), '\t', ' ');
            removeSpaces();
            std::size_t index = query.find_first_of('?');
            if (index == std::string::npos){
                cout << "Invalid query entered.\n(Enter 'Exit?' to exit OR 'What is the most current popular itemID?' to find the most popular id.)";
                continue;
            }
            else if( index != query.length()-1) { 
                if ( query.substr(index, query.length()-index) != string(query.length()-index, '?') ){
                    cout << "Invalid query entered.\n(Enter 'Exit?' to exit OR 'What is the most current popular itemID?' to find the most popular id.)";
                    continue;
                }
                query.erase(index+1, query.length()-index); 
            }
            if(query == "exit?"){
                interruptFlag = true;
                break;
            }
            if (query != "what is the most current popular itemid?"){
                cout << "\nInvalid query entered.\n(Enter 'Exit?' to exit OR 'What is the most current popular itemID?' to find the most popular id.)\n\n";
                continue;
            }
            else{
                string id = computeTheMostPopularItemId();
                if (id != ""){
                    cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
                    cout << "\nThe Most Popular item details are: \n";
                    cout << "\nItem ID is -> "<< id;
                    cout << "\nCurrent timestamp is -> " << currentTimestamp;
                    cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n";
                }
            }

        } 
        catch(...){
            cout << "\nError in parsing input data. Please Try Again\n";
        }
    }

}

void ConsoleThread::removeSpaces()
{
    int n = query.length();
 
    int i = 0, j = -1;

    bool spaceFound = false;
    while (++j < n && query[j] == ' ');

    while (j < n)
    {
        if (query[j] != ' ')
        {
            if (query[j] == '?' && i - 1 >= 0 &&
                 query[i - 1] == ' ')
                query[i - 1] = query[j++];
 
            else
                query[i++] = query[j++];
            spaceFound = false;
        }
        else if (query[j++] == ' ')
        {
            if (!spaceFound)
            {
                query[i++] = ' ';
                spaceFound = true;
            }
        }
    }
 
    if (i <= 1)
        query.erase(query.begin() + i, query.end());
    else
        query.erase(query.begin() + i, query.end());
}

string ConsoleThread::computeTheMostPopularItemId(){
    map<string, vector<double>>::iterator it = mostPopItem.begin();

    double compare = -1;
    string key = "";
    for(; it != mostPopItem.end(); ++it){

        if (compare < (it->second)[0]){
            key = it->first;
            compare = (it->second)[0];
        }
    }
    return key;
}

