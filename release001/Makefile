happyfish: main.o CClient.o CDataBase.o CNetworkClient.o CNetworkServer.o CWorker.o
	g++ -g -o happyfish main.o CClient.o CDataBase.o CNetworkClient.o CNetworkServer.o CWorker.o
main.o: main.cpp 
	g++ -c -g main.cpp
CClient.o: CClient.cpp CClient.h
	g++ -c -g CClient.cpp
CDataBase.o: CDataBase.cpp CDataBase.h
	g++ -c -g CDataBase.cpp
CNetworkClient.o: CNetworkClient.cpp CNetworkClient.h
	g++ -c -g CNetworkClient.cpp 
CNetworkServer.o: CNetworkServer.cpp CNetworkServer.h
	g++ -c -g CNetworkServer.cpp
CWorker.o: CWorker.cpp CWorker.h
	g++ -c -g CWorker.cpp
clean:
	rm *.o happyfish
