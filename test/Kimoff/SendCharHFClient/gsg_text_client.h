#ifndef TEXT_CLIENT
#define TEXT_CLIENT

#include "gsg_nscreen.h"
#include <pthread.h>
#include <string>

struct XYcords
{
  int xmax;
  int ymax;
};

extern WINDOW* bwin;
extern WINDOW* swin;
extern pthread_mutex_t lockx;
extern std::string temp;

void InitTextClient(XYcords &cords);
void GetUserString(std::string &str, NetworkClient* client);
int StartNetworkListen(void* cl);
void StartNetworkSend(NetworkClient* client);
void* NetworkListen(void* client_void);

#endif
