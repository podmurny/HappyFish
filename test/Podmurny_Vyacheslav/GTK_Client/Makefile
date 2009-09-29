GSGgtk.out : main.o GSGgtk.o
	g++ -g -o GSGgtk.out main.o GSGgtk.o
main.o : main.cpp
	g++ -g -c main.cpp GSGgtk.h
GSGgtk.o : GSGgtk.cpp GSGgtk.h
	g++ -g -c `pkg-config --cflags --libs gtk+-2.0` GSGgtk.cpp
clean:
	rm *.out *.o
