#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "SqliteDatabase.h"
#include "LoggedUser.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include <iostream>

class LoginRequestHandler;
class MenuRequestHandler;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler();
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	StatisticsManager m_statisticsManager;
	RoomManager m_roomManager;
};