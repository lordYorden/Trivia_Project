#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"
#include "IDatabase.h"
#include "ExceptionHandler.h"
#include <exception>
#include <string>
class LoginManager
{
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
	bool isValidUname(std::string name);
public:
	LoginManager(IDatabase* database);
	~LoginManager();
	void signup(std::string name, std::string password, std::string mail);
	void login(std::string name, std::string password);
	void logout(std::string name);
};