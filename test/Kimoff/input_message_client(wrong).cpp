     #include <iostream>	//stream i/o
     #include <stdlib.h>
     #include <stdio.h>
     
     #include <termios.h>	//To change terminal input mode
     #include <string.h>

using namespace std;

const int BUFFER_SIZE = 1024;
     
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

char buffer[BUFFER_SIZE];	//BUFFER

//Function for correct message input
void enter(char* buf, bool interrupt)	//Parameter given by reference
{
	set_keypress();		//Set terminal into non-canonical mode to get pressed key immediately, but not after pressing ENTER
	char c;
	int i = 0; 
	while(1)
	{
		if (interrupt == true)	//If input is interrupted
		{
			sleep(1);				//Wait a second
			for(int j=0; j<i; j++) cout<<buf[j];	//Print again all already inserted in buffer symbols and continue inputing
		}
		c = (char)getchar();
		if (c == '\n') break; 	//If enter is pushed
		buf[i] = c;		//Write entered symbol to buffer
		i++;		
	}
	reset_keypress();	//Reset terminal into canonical mode
}

int main()
{
	bool interruption_flag = false;
	enter(buffer,interruption_flag);
	cout<<endl<<buffer<<endl;
	getchar();
	return 0;
}
