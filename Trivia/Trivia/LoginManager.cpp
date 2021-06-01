#include "LoginManager.h"

bool LoginManager::isValidUname(std::string name)
{
	bool flag = true;
	for (int i = 0; i < name.length() && flag; i++)
	{
		if (!std::isalnum(name[i]))
		{
			flag = false;
		}
	}
	return flag;
}

LoginManager::LoginManager(IDatabase* database):
	m_database(database)
{
}

LoginManager::~LoginManager()
{
	this->m_loggedUsers.clear();
}

void LoginManager::signup(std::string name, std::string password, std::string mail)
{
	if (!isValidUname(name))
	{
		throw ExceptionHandler("Error!....Username contains invalid cherecters (Can only put Letters and Numbers)");
	}
	else if (m_database->doesUserExist(name)) 
	{
		throw ExceptionHandler("Error!....User already exist");
	}
	else
	{
		m_database->addNewUser(name, password, mail);
		m_loggedUsers.push_back(LoggedUser(name));
	}
}

void LoginManager::login(std::string name, std::string password)
{
	if (std::find(m_loggedUsers.begin(), m_loggedUsers.end(), LoggedUser(name)) != m_loggedUsers.end())
	{
		throw ExceptionHandler("Error!....Username already logged in");
	}
	if (!m_database->doesUserExist(name) || !m_database->doesPasswordMatch(name, password))
	{
		throw ExceptionHandler("Error!....Username or Password weren't found");
	}
	else
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
			return;
		}
	}
}


