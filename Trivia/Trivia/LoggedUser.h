#pragma once
#include <iostream>
class LoggedUser
{
private:
	std::string m_username;
public:
	std::string getUsername()
	{
		return m_username;
	}
	LoggedUser(std::string uname)
	{
		m_username = uname;
	}
	
};