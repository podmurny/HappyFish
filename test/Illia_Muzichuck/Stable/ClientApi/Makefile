#Это Makefile является простым примером как собрать проэкт с использованием NetworkClient
# main.cpp - это файл с программой, которая использует NetworkClient
client_objects = NetworkClient.o gsg_socket.o main.o

client: $(client_objects)
	g++ -o client $(client_objects) -g

NetworkClient.o: NetworkClient.cpp
gsg_socket.o: gsg_socket.cpp
main.o: main.cpp

clean:
	rm -f *.o