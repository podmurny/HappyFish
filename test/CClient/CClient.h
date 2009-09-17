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
	private:
		std::string message;
		std::string name;
};
#endif