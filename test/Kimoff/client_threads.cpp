#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <cstring>
#include <sstream>
#include <termios.h>	//To change terminal input mode

using namespace std;

const int BUFFER_SIZE = 1024;

struct Message
{
  string receiver;
  string data;
};

static struct termios stored_settings;
     
void set_keypress(void)	//Set terminal into non-canonical mode to get pressed button emmidiately
{
    struct termios new_settings;
     
    tcgetattr(0,&stored_settings);
     
    new_settings = stored_settings;
     
    /* Disable canonical mode, and set buffer size to 1 byte */
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;
     
    tcsetattr(0,TCSANOW,&new_settings);
    return;
}
     
void reset_keypress(void)	//Restore terminal to the canonical mode
{
    tcsetattr(0,TCSANOW,&stored_settings);
    return;
}

	bool interrupt = false;		//Boolean flag for input interruption state, caused by receiving a message	

//Function for correct message input
void enter(char* buf, bool interrupt)	//Parameter given by reference
{
	bzero(buf,BUFFER_SIZE);
	set_keypress();		//Set terminal into non-canonical mode to get pressed key immediately, but not after pressing ENTER
	char c;
	int i = 0; 
	cout<<"Enter message: ";
	while(1)
	{
		if (interrupt == true)	//If input is interrupted
		{
			sleep(1);				//Wait a second
			cout<<"Enter message: ";
			for(int j=0; j<i; j++) cout<<buf[j];	//Print again all already inserted in buffer symbols and continue inputing
			interrupt = false;
		}
		c = (char)getchar();
		if (c == '\n') break; 	//If enter is pushed
		buf[i] = c;		//Write entered symbol to buffer
		i++;		
	}
	reset_keypress();	//Reset terminal into canonical mode
}

/*void* thr_send(void* ID)		//Message send thread (not yet synchronized with message receive thread)
{
	int* intPtr = (int*)ID;	//Convert void* to int*
	int sockID = *intPtr;	//Get data into int variable

	while(1)
	{
		string buf;
		cout<<"Enter message: ";
		cin>>buf;
		if (buf == "quit") break;
		send(sockID, buf.data(), buf.length(), 0);	//Send message to the server
	}
}*/

void* thr_recv(void* ID)		//Message receive thread
{
	int* intPtr = (int*)ID;	//Convert void* to int*
	int sockID = *intPtr;	//Get data into int variable

	char buf[BUFFER_SIZE];
      	int bytes_read;
      	while(1)
	{
	  	bzero(buf,sizeof(buf));
	  	bytes_read = recv(sockID, buf, BUFFER_SIZE, 0);		//Receive message from the server
	  	if(bytes_read >= 0)
	  	{
			interrupt = true;
	      		cout<<endl<<"Message from server: "<<buf<<endl;	//Print received message
	  	}
	}
}	

int main()
{
    int sock;	//Socket id
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);	//Initialise socket

    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234); 	//Server port
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    connect(sock, (struct sockaddr *)&addr, sizeof(addr));	//Connect socket to the port

	//pthread_t sendThr;		//Message send thread id
	pthread_t recvThr;		//Message receive thread id

	pthread_create(&recvThr,0,&thr_recv,(void*)&sock);	//Receiving is processed in this thread		
	//pthread_create(&sendThr,0,&thr_send,(void*)&sock);	//Sending is processed in this thread	

	char buf[BUFFER_SIZE];
	string mes;		//Buffer for the message

	while(1)
	{
		enter(buf,interrupt);
		mes = "";
		for(int i=0;i<BUFFER_SIZE;i++)
			mes+=buf[i];
			
		send(sock, mes.data(), mes.length(), 0);	//Send message to the server
	}	
		
		
    close(sock);		//Close socket

    return 0;
}
