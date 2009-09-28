CClient.out : main.o CClient.o
	g++ -g -o CClient.out main.o CClient.o
main.o: main.cpp
	g++ -c -g main.cpp CClient.h
CClient.o: CClient.cpp CClient.h
	g++ -c -g CClient.cpp
clean:
	rm *.out *.o
