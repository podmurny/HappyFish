#ifndef DBC
#define DBC

#include <stdlib.h>
#include <string>
using std::string;

class hfm_db {
public:
  void add_user(const char* UID, const char* password);

  void drop_user(const char UID, const char password);

  void update_user_info(const char UID, const char password, const char full_name, const char country, const char city, const char language, 
			const char birthday, const char about);
  
  int logon_user(const char* UID, string password);

};

#endif
