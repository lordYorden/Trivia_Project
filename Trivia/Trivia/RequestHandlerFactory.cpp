#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"

/*
* RequestHandlerFactory class constractor
* gets a db pointer and create a login manager
* input: factory - the sqlite db (Idatabase*)
* output: none
*/
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database):
	m_database(database), m_loginManager(LoginManager(database))
{
}

/*
* RequestHandlerFactory class distractor
* deletes the db instance
* input: none
* output: none
*/
RequestHandlerFactory::~RequestHandlerFactory()
{
	delete m_database;
	m_database = nullptr;
}

/*
* creates a login Request Handler
* input: none
* output: handler - handler to mannage client login (LoginRequestHandler*)  
*/
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

/*
* return the login manager of the factory
* input: none
* output: the factory login manager
*/
LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}