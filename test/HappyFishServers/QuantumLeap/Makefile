server_objects = main.o gsg_socket.o SocketTable.o ServerCore.o ActionQueue.o

server: $(server_objects)
	g++ -o server -g $(server_objects)

main.o: main.cpp
	g++ -c main.cpp -g
gsg_socket.o: gsg_socket.cpp
	g++ -c gsg_socket.cpp -g
SocketTable.o: SocketTable.cpp
ServerCore.o: ServerCore.cpp
ActionQueue.o: ActionQueue.cpp

clean:
	rm -f *.o
