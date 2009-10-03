client_objects = NetworkClient.o gsg_socket.o main.o gsg_nscreen.o gsg_text_client.o

client: $(client_objects)
	g++ -o client $(client_objects) -g -lpthread -lncurses

NetworkClient.o: NetworkClient.cpp
gsg_socket.o: gsg_socket.cpp
main.o: main.cpp
gsg_nscreen.o: gsg_nscreen.cpp
gsg_text_client.o: gsg_text_client.cpp

clean:
	rm -f *.o