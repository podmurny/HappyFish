#include "CClient.h"
#include <time.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

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
    std::ofstream file_chat;
    file_chat.open("/home/slava/chat.txt");
    std::string current_time = get_date_time();
    current_time.resize((current_time.length() - 1) );
    file_chat <<"Status: "<< current_time << " sender: " << name1 << "\n" ;
    file_chat << "Message: " << message1;
    file_chat.close();
    return 0;
}
int CClient::write_log_to_file(std::string& message1)
{
    std::ofstream log_file("logfile.txt", std::ios::app);
    if(log_file.is_open())
    {
        std::string current_time = get_date_time();
        current_time.resize((current_time.length() - 1) );
        log_file << current_time << "\n" << message1 <<"\n";
        return 0;
    }
    else
    {
        return 1;
    }
}
std::string CClient::read_message_from_file()
{
    std::ifstream file_chat("/home/slava/chat.txt",std::ios::ate);
    if(file_chat.is_open())
    {
        getline(file_chat,message);
        
        return message;
    }
    else
    {
        return "0";
    }
    
}