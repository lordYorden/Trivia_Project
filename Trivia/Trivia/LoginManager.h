#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"
#include "IDatabase.h"
class LoginManager
{
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
public:
	void signup(std::string name, std::string password, std::string mail);
	void login(std::string name, std::string password);
	void logout(std::string name);

	
};