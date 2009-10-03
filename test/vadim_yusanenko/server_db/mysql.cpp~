// 0.3 Версия кода
// TODO: Откомментить все классы и функции, семантика, void -> int, use try catch, write manual=)
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
	query << "INSERT INTO Accounts VALUES ('" << UID << "', '" << password << ");";
	query.execute();
}

void drop_user(const char UID) {
	Connection conn(false);
	conn.connect("Test", "localhost", "root", "qwerty");
	Query query = conn.query();
	query << "DELETE FROM Accounts WHERE UID='" << UID << "');";
	query.execute();
}

int logon_user(const char UID, const char password) {
	Connection conn(false);
	conn.connect("Test", "localhost", "root", "qwerty");
	Query query = conn.query();
	query << "SELECT PASS FROM Accounts WHERE UID='" << UID << "');";
	query.execute();
	StoreQueryResult result = query.store();
	if (!result[1]["PASS"] == password) return -1; else return 0;
}

};

int main()
{ return 0; }

