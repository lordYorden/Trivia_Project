#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "SqliteDatabase.h"
#include "LoggedUser.h"
#include <iostream>

class LoginRequestHandler;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
};