#include "Client.hpp"
#include "GlobalVars.hpp"

Client::Client(string host, int port){
    this->ipAddress = host;
    this->port = port;
    this->sock = -1;
}

bool Client::connectToServer(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if ( sock < 0 ){
        cout << "\nError in Creating Socket. Exiting!!!!\n";
        return false;
    }
    
    memset(&serAddress, '0', sizeof(serAddress));
  
    serAddress.sin_family = AF_INET;
    serAddress.sin_port = htons(port);

    if (checkValidIpAddress() == false)
        return false;

    if (connect(sock, (struct sockaddr *)&serAddress, sizeof(serAddress)) < 0){
        cout << "\nConnection Failed. Exiting!!!!\n";
        return false;
    }

    return true;
}


bool Client::checkValidIpAddress(){
    if(inet_addr(ipAddress.c_str()) == -1){
        struct hostent *ht;
        struct in_addr **addr_list;

        ht = gethostbyname( ipAddress.c_str() ) ;
        if ( ht == NULL){
            cout << "\nFailed to resolve hostname. Exiting!!!!\n";
            return false;
        }

        addr_list = (struct in_addr **) ht->h_addr_list;
        for(int i = 0; addr_list[i] != NULL; i++){
            serAddress.sin_addr = *addr_list[i];
            //cout<< ipAddress <<" resolved to "<<inet_ntoa(*addr_list[i])<<endl;
            break;
        }
    }
    else{
        serAddress.sin_addr.s_addr = inet_addr( ipAddress.c_str() );
    }

    return true;
}

void Client::readDataFromServer(){
    int valread;
    char buffer[65536];
    string reply;
    string leftOver = "";
    while ( buffer != NULL ){
        valread = read( sock , buffer, 65536);
        if ( valread <= 0){
            clientFlag = true;
            cout << "\nConnection to Server lost. Exiting ClientThread\n";
            close(sock);
            break;
        }
        if (interruptFlag == true || computeFlag == true){
            cout << "\nExiting Client Thread due to interrupt\n";
            clientFlag = true;
            close(sock);
            break;
        }

        buffer[valread] = '\0';
        string temp = buffer;
        std::size_t found = temp.find_last_of('\n');
        
        mtx.lock();
        addDataList.push(leftOver + temp.substr(0, found));
        //addData = addData + "\n" +leftOver + temp.substr(0, found);
        //addData = addData + "\n" + temp;
        mtx.unlock();
        leftOver = temp.substr(found+1, (temp.length()-1));
    }
    clientFlag = true;
}




