#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomRequestHandler.h"
#include "GameRequestHandler.h"

/*
* RequestHandlerFactory class constractor
* gets a db pointer and create a login manager
* input: factory - the sqlite db (Idatabase*)
* output: none
*/
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database):
	m_database(database), m_loginManager(LoginManager(database)), m_statisticsManager(database), m_gameManager(database)
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

/*
* creates a Menu Request Handler
* input: none
* output: handler - handler to Menu requests (MenuRequestHandler*)
*/
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser& user)
{
	return new MenuRequestHandler(*this, user);
}

/*
* return the statistics manager of the factory
* input: none
* output: the factory statistics manager
*/
StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_statisticsManager;
}

/*
* return the room manager of the factory
* input: none
* output: the factory room manager
*/
RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

/*
* creates a Room Admin Request Handler
* input: none
* output: handler - handler to mannage client login (RoomAdminRequestHandler*)
*/
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(int RoomID, LoggedUser& user)
{
	return new RoomAdminRequestHandler(*this, user, m_roomManager.getRoomById(RoomID));
}

/*
* creates a Room Member Request Handler
* input: none
* output: handler - handler to mannage client login (RoomMemberRequestHandler*)
*/
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(int RoomID, LoggedUser& user)
{
	return new RoomMemberRequestHandler(*this, user, m_roomManager.getRoomById(RoomID));
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(Game& game, LoggedUser& user)
{
	return new GameRequestHandler(*this, user, game);
}

GameManager& RequestHandlerFactory::getGameManager()
{
	return this->m_gameManager;
}
