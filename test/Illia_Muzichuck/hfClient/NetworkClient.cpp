#include "NetworkClient.h"

NetworkClient::NetworkClient()
  :client_sock_fd(-1),valid(DISCONNECT)
{
  bzero(&server_addr,sizeof(server_addr));
}

NetworkClient::~NetworkClient()
{
  Disconnect();
}

void NetworkClient::SetValid(int v)
{
  valid = v;
}

void NetworkClient::ConnectToServer(int port, const char* ipstr)
{
  client_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(client_sock_fd <= 0){
    return;}
  if(Connect(server_addr, client_sock_fd, ipstr, port) < 0){
    return;}
  SetValid(CONNECT);
}

void NetworkClient::Disconnect()
{
  close(client_sock_fd);
  bzero(&server_addr,sizeof(server_addr));
  SetValid(DISCONNECT);
}

int NetworkClient::SendMsg(std::string msg)
{
  if(valid = DISCONNECT){
    return -1;}
  int bytes_send;
  bytes_send = send(client_sock_fd, msg.data(), msg.length(), 0);
  if(bytes_send <=0 ){
    return -1;}
  return bytes_send;
}

int NetworkClient::WaitMsg(char* buffer, int size)
{
  if(valid = DISCONNECT){
    return -1;}
  int bytes_read = 0;
  bzero(buffer,size);
  bytes_read = recv(client_sock_fd, buffer, size, 0);
  if(bytes_read <= 0){
    return -1;}
  return bytes_read;
}
