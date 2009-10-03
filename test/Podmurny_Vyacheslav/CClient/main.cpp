#include "CClient.h"
#include <string>
#include <stdio.h>
int main()
{

        CClient client("/home/slava/log.txt");
//	std::string st;
//	st=client.get_date_time();
//        std::string st("slava");
//        std::string st1("hello world");
//        client.write_message_to_file(st,st1);
//        std::string str;
//       str = client.read_message_from_file();
		std::string st;
		st = "slava log file";
        client.write_log_to_file(st);
		

        return 0;
    
	
}

