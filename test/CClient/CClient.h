#ifndef CCLIENT_H
#define CCLIENT_H
#include <string>
#include <stdio.h>

class CClient
{
	public:
		CClient();
		std::string get_date_time();		
		int write_message_to_file(std::string& name1,std::string& message1);
                std::string read_message_from_file();
                std::string get_message();
                int set_message(std::string& message1);
                std::string get_name();
                int set_name(std::string& name1);
	private:
		std::string message;
		std::string name;
};
#endif