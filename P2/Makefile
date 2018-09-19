all:	GlobalVars.hpp Main.cpp Client.cpp  Client.hpp  ClientThread.cpp  ClientThread.hpp  ConsoleThread.cpp  ConsoleThread.hpp AddDataToMap.cpp AddDataToMap.hpp
	g++ -o P2 GlobalVars.hpp Main.cpp Client.cpp  Client.hpp  ClientThread.cpp  ClientThread.hpp  ConsoleThread.cpp  ConsoleThread.hpp AddDataToMap.cpp AddDataToMap.hpp -std=c++11 -l pthread
debug:	GlobalVars.hpp Main.cpp Client.cpp  Client.hpp  ClientThread.cpp  ClientThread.hpp  ConsoleThread.cpp  ConsoleThread.hpp AddDataToMap.cpp AddDataToMap.hpp
	g++ -g -o P2 GlobalVars.hpp Main.cpp Client.cpp  Client.hpp  ClientThread.cpp  ClientThread.hpp  ConsoleThread.cpp  ConsoleThread.hpp AddDataToMap.cpp AddDataToMap.hpp -std=c++11 -l pthread
clean:
	rm -rf *.o *~ P2 core
