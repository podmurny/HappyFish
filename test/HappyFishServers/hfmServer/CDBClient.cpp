#include "CDBClient.h"

#include <mysql++/mysql++.h>
#include <iostream>
using namespace std;
using namespace mysqlpp;


void hfm_db::add_user(const char* UID, const char* password) { 
  Connection conn(false);
  conn.connect("Test", "localhost", "root", "qwerty");
  Query query = conn.query();
  query << "INSERT INTO Accounts VALUES ('" << UID << "', '" << password << "', NULL, NULL, NULL, NULL, NULL, NULL);";
  query.execute();
}

void hfm_db::drop_user(const char UID, const char password) {
  Connection conn(false);
  conn.connect("Test", "localhost", "root", "qwerty");
  Query query = conn.query();
  query << "DELETE FROM Accounts WHERE UID=" << UID << " AND PASS='" << password << "');";
  query.execute();
}

void hfm_db::update_user_info(const char UID, const char password, const char full_name, const char country, const char city, const char language, 
			      const char birthday, const char about) {
  Connection conn(false);
  conn.connect("Test", "localhost", "root", "qwerty");
  Query query = conn.query();
  query << "UPDATE Accounts SET Full_name='" << full_name << "', Country='" << country << "', City='" << city << "', Language='"
	<< language << "', Birthday='" << birthday << "', About='" << about << "' WHERE UID='" << UID << "' AND PASS='" << password << "');";
  query.execute();
}

int hfm_db::logon_user(const char* UID, const string password) {
  try
    {
      Connection conn(false);
      conn.connect("Test", "localhost", "root", "qwerty");
      
      string cStr(UID); 
      string qStr = "SELECT PASS FROM Accounts WHERE UID='" + cStr + "';";

      Query query = conn.query(qStr);
      
      //cout<<qStr<<endl;
      
      StoreQueryResult result = query.store();
      if(result.num_rows() == 0)
	return -1;
      string checkStr;
      result[0][0].to_string(checkStr);
      
      //cout<<checkStr<<" "<<password<<endl;
      
      if(checkStr == password)
	return 0;
      return -1;
    }
  catch(const mysqlpp::Exception& er)
    {
      return -1;
    }
}
