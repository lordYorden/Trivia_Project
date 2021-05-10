#include "SqliteDatabase.h"
#include "sqlite3.h"
void SqliteDatabase::open()
{
	std::string dbFileName = "UserDB.sqlite";
	int res = sqlite3_open(dbFileName.c_str(), &_db);
	if (res != SQLITE_OK) {
		_db = NULL;
		std::cout << "Failed to open DB" << std::endl;
	}
	std::cout << "opend" << std::endl;
	std::string statement = "CREATE TABLE IF NOT EXISTS USERS(UNAME TEXT NOT NULL PRIMARY KEY,PASSWORD TEXT NOT NULL,MAIL TEXT NOT NULL);";
	ExecuteSQL(statement);
}


void SqliteDatabase::ExecuteSQL(std::string statement)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->_db, statement.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << "Failed SQL" << std::endl;
		return;
	}
	return;
}


bool SqliteDatabase::doesUserExist(std::string name)
{
	bool flag = false;
	std::string statement = "SELECT * FROM USERS WHERE UNAME = \"" + name + "\";";
	ExecuteSqlCallback(statement, isExistsCallback, &flag);
	return flag;

}

bool SqliteDatabase::doesPasswordMatch(std::string name, std::string password)
{
	bool flag = false;
	std::string statement = "SELECT * FROM USERS WHERE UNAME = \"" + name + "\" AND PASSWORD = \"" + password + "\";";
	ExecuteSqlCallback(statement, isExistsCallback, &flag);
	return flag;
}

void SqliteDatabase::addNewUser(std::string name, std::string password, std::string mail)
{
	std::string statement = "INSERT INTO USERS(UNAME,PASSWORD,MAIL)\ VALUES(\"" + name + "\",\"" + password + "\",\"" + mail + "\");";
	ExecuteSQL(statement);
}

void SqliteDatabase::ExecuteSqlCallback(std::string statement, int(*callback)(void*, int, char**, char**), void* data)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->_db, statement.c_str(), callback, data, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << "Failed SQL" << std::endl;
		return;
	}

	return;
}
int SqliteDatabase::isExistsCallback(void* data, int argc, char** argv, char** azColName)
{
	*(bool*)data = true;
	return 0;
}
