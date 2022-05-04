#pragma once
#include <iostream>
class LoggedUser
{
private:
	std::string m_username;
public:
	std::string getUsername() const
	{
		return m_username;
	}
	LoggedUser(std::string uname)
	{
		m_username = uname;
	}
	bool operator==(LoggedUser const& other) 
	{
		return this->m_username == other.m_username;
	}

	bool operator<(const LoggedUser& other) const
	{
		return this->m_username.length() < other.m_username.length();
	}
	
};