#include "CClient.h"
#include <string>
int main()
{

        CClient client;
//	std::string st;
//	st=client.get_date_time();
//        std::string st("slava");
//        std::string st1("hello world");
//        client.write_message_to_file(st,st1);
        std::string str;
        str = client.read_message_from_file();
        return 0;
}
