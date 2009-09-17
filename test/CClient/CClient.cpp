#include "CClient.h"
#include <time.h>
#include <stdio.h>
#include <string>
CClient::CClient()
{
}
std::string CClient::get_date_time()
{
	time_t rawtime;
	time ( &rawtime );
	return ctime(&rawtime);
}
int CClient::write_message_to_file(std::string& name1,std::string& message1)
{
	return 0;
}
