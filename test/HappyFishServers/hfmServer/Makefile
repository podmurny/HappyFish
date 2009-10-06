client_objects = main.o SocketTable.o gsg_socket.o ServerCore.o CDBClient.o
server: $(client_objects)
	g++ -o server -fPIC $(client_objects) `mysql_config --libs --cflags` -lpthread -lmysqlpp -I/usr/include/mysql++

main.o: main.cpp
SocketTable.o: SocketTable.cpp
gsg_socket.o: gsg_socket.cpp
ServerCore.o: ServerCore.cpp ServerCore.h
CDBClient.o: CDBClient.cpp
	g++ -c -fPIC CDBClient.cpp `mysql_config --libs --cflags` -lmysqlpp -I/usr/include/mysql++

clean:
	rm -f *.o