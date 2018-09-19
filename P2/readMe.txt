Steps for running the code:
1) Type make --> to compile the code
2) ./P2 portNo --> to run the client
Enter decay constant: 0.99 (P2 will ask for the decay constant)
Once connection is make you can fire the following query anytime(it is case insensitive):
1) What is the most current popularItemID?
2) Exit?
      
Test Cases:
I have tested the code for the following:
    a) Invalid query
    b) Invalid port
    c) Invalid decay
    c) Data with same item repeating multiple times
    
Note:
If the code receives an invalid chunk of data, then at the time of parsing, it will simply log error, skip that chunk and continue operation.
Once all the data is received from server, Application waits for all the data to get processed and then exits.

Overview of the code:
Main.cpp:
This file creates 3 threads
    a) Client Thread: It connects to the server and reads data
    b) ConsoleThread: It keeps listening to the queries entered by user.
    c) computeThread: It operates on the data send by server
Main thread waits for the clientThread and computeThread to finish execution.
Once done it kills the consoleThread and exits.
If user press control+C, this signal is handled in the main thread. Main thread orders all clients to exit and wait till the compute thread and client thread are killed. Then it exits.

ClientThread.cpp:
This is a thread class which uses function objects ie we are overloading '()' operator
It creates a client object, through client object makes a connection with server and reads data.

Client.cpp
This class makes a connection with the server using sockets and read data. 
Here we check if ip address is valid or it is the host name and map it to ip.
We continuously read data until server closes the connection. Once the connection is closed, client thread kills itself, It also sets flag to kill the compute thread once all the data is processed. If there is an interrupt in the system, main threads set the interrupt flag and client thread exits in that case too.
Client saves the data read from server in a queue of string which is shared with the AddDataToMap.cpp file and thus we are using mutex lock.

AddDataToMap.cpp
This is the console thread. It is parsing the data received from server and adding it to the dataMap. We are pooping data from the addData queue with taking a lock as it is being shared with CLientThread.
We are separating string data based on "\n" and then splitting based on space to get the key and value.
This key and value we are storing in a map with key as the item id and the values is a size 2 vector with first index storing the decay value and second index holding the timestamp.

ConsoleThread.cpp  
This thread parses the query done by client. It makes the string lower case, checks whether the question is valid. 
If question is invalid, it shows the valid inputs and prompts user to enter query again.
If question is valid, it will parse the map and fetch the itemId with maximum decay value and outputs the data along with the current timestamp.
ConsoleThreads kills itself if user types exit? and sets exit flags for compute thread and client thread.

