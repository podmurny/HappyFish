GSGgtk.out :  GSGgtk.o
	g++ -g -o GSGgtk.out  GSGgtk.o
GSGgtk.o : GSGgtk.cpp GSGgtk.h
	g++ -g -c `pkg-config --cflags --libs gtk+-2.0` GSGgtk.cpp
clean:
	rm *.out *.o
