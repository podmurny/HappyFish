// 0.4.3 Версия кода
// TODO: Откомментить все классы и функции, семантика, void -> int, use try catch, write manual
#include <mysql++.h>
#include <stdlib.h>

using namespace std;
using namespace mysqlpp;

class hfm_db {
public:

Connection conn;
unsigned int affected_rows;

hfm_db(const char db[], const char db_host[], const char db_username[], const char db_password[]) {
conn.connect(db, db_host, db_username, db_password);
}

void add_user(const char UID[], const char password[]) { 
	Query query = conn.query();
	query << "INSERT INTO Accounts VALUES ('" << UID << "', '" << password << "');";
	query.execute();
	//affected_rows = query.affected_rows();
}

void drop_user(const char UID[]) {
	Query query = conn.query();
	query << "DELETE FROM Accounts WHERE UID='" << UID << "');";
	query.execute();
}

int logon_user(const char UID[], const char password[]) {
	Query query = conn.query();
	query << "SELECT PASS FROM Accounts WHERE UID='" << UID << "');";
	query.execute();
	StoreQueryResult result = query.store();
	if (result[0]["PASS"] != password) return -1; else return 0;
}

};

int main() {
hfm_db hfm_db1("Test", "localhost", "root", ".cfytyrjNHBCNFVdflbv");
hfm_db1.add_user("vova", "qwerty");
hfm_db1.add_user("lida", "qwerty");
return 0; 
}

