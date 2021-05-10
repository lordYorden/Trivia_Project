#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
class SqliteDatabase : public IDatabase
{
public:
	bool doesUserExist(std::string name) override;
	bool doesPasswordMatch(std::string name, std::string password)override;
	void addNewUser(std::string name, std::string password, std::string mail)override;
	
	void ExecuteSQL(std::string statement);
	void ExecuteSqlCallback(std::string statement, int(*callback)(void*, int, char**, char**), void* data);
	void open();
private:

	static int isExistsCallback(void* data, int argc, char** argv, char** azColName);
	sqlite3* _db;

};