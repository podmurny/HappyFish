#include <mysql++.h>
#include <stdlib.h>

using namespace std;
using namespace mysqlpp;

class hfm_db {
public:

void add_user(const char UID, const char password) { 
	Connection conn(false);
	conn.connect("Test", "localhost", "root", "qwerty");
	Query query = conn.query();
	query << "INSERT INTO Accounts VALUES (" << UID << ", '" << password << "', NULL, NULL, NULL, NULL, NULL, NULL);";
	query.execute();
}

void drop_user(const char UID, const char password) {
	Connection conn(false);
	conn.connect("Test", "localhost", "root", "qwerty");
	Query query = conn.query();
	query << "DELETE FROM Accounts WHERE UID=" << UID << " AND PASS='" << password << "');";
	query.execute();
}

void update_user_info(const char UID, const char password, const char full_name, const char country, const char city, const char language, 
const char birthday, const char about) {
	Connection conn(false);
	conn.connect("Test", "localhost", "root", "qwerty");
	Query query = conn.query();
	query << "UPDATE Accounts SET Full_name='" << full_name << "', Country='" << country << "', City='" << city << "', Language='"
	<< language << "', Birthday='" << birthday << "', About='" << about << "' WHERE UID='" << UID << "' AND PASS='" << password << "');";
	query.execute();
}

int logon_user(const char UID, const char password) {
	Connection conn(false);
	conn.connect("Test", "localhost", "root", "qwerty");
	Query query = conn.query();
	query << "SELECT PASS FROM Accounts WHERE UID='" << UID << "');";
	query.execute();
	StoreQueryResult result = query.store();
	if (!result[0]["PASS"] == password) return -1; else return 0;
}

};
