#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "SqliteDatabase.h"
#include "LoggedUser.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "GameManager.h"
#include "Game.h"
#include <iostream>

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser& user);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
	RoomAdminRequestHandler* createRoomAdminRequestHandler(int RoomID, LoggedUser& user);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(int RoomID, LoggedUser& user);
	GameRequestHandler* createGameRequestHandler(Game& game, LoggedUser& user);
	GameManager& getGameManager();
	
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	StatisticsManager m_statisticsManager;
	RoomManager m_roomManager;
	GameManager m_gameManager;
};