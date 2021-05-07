#include "LoginManager.h"

void LoginManager::signup(std::string name, std::string password, std::string mail)
{
	m_database->addNewUser(name, password, mail);
}

void LoginManager::login(std::string name, std::string password)
{
	if (m_database->doesUserExist(name) && m_database->doesPasswordMatch(name, password))
	{
		m_loggedUsers.push_back(LoggedUser(name));
	}
}

void LoginManager::logout(std::string name)
{
	for (std::vector<LoggedUser>::iterator it = m_loggedUsers.begin(); it != m_loggedUsers.end(); it++)
	{
		if (it->getUsername() == name)
		{
			m_loggedUsers.erase(it);
		}
	}
}
