#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct Message
{
  string receiver;
  string data;
};

int main()
{
    int sock;	//Socket id
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);	//Initialise socket

    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234); 	//Server port
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    connect(sock, (struct sockaddr *)&addr, sizeof(addr));	//Connect socket to the port

	Message Msg;		//Create test message
	Msg.receiver = "1";
	Msg.data = "Bravo Charlie Omega";

	string str = Msg.receiver+"*"+Msg.data;
	cout<<str<<endl;

	switch(fork())
    	{
    		case (pid_t) -1:
      			perror("fork");
      			return 0;
      			break;
    		case (pid_t) 0:			//Child process (sending messages)
      			while(1)
			{
	  			string buf;
	  			cout<<"Enter message: ";
	  			cin>>buf;
	  			send(sock, buf.data(), buf.length(), 0);	//Send message to the server
			}
      			break;
    		default:			//Parent process (receiving messages)
      			char buf[1024];
      			int bytes_read;
      			while(1)
			{
	  			bzero(buf,sizeof(buf));
	  			bytes_read = recv(sock, buf, 1024, 0);		//Receive message from the server
	  			if(bytes_read >= 0)
	  			{
	      				cout<<endl<<"Message from server: "<<buf<<endl<<"Enter message: ";	//Print received message
	  			}
			}
    }
		
    close(sock);		//Close socket

    return 0;
}
