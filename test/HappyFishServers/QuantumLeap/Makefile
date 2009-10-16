server_objects = main.o gsg_socket.o UsersTable.o ServerCore.o RoundQueue.o

server: $(server_objects)
	g++ -o server -g $(server_objects)

main.o: main.cpp
	g++ -c main.cpp -g
gsg_socket.o: gsg_socket.cpp
	g++ -c gsg_socket.cpp -g
UsersTable.o: UsersTable.cpp
ServerCore.o: ServerCore.cpp
RoundQueue.o: RoundQueue.cpp
clean:
	rm -f *.o
