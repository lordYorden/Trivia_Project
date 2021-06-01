#pragma once
#include "IRequestHandler.h"
#include "JsonResponseSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "StatisticsManager.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "IRequestHandler.h"
#include <ctime>
#include <chrono>

class RequestHandlerFactory;
class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& Factory, LoggedUser& User);
	~MenuRequestHandler();
	virtual bool isRequestRelevent(RequestInfo info) override;
	virtual RequestResult RequestHandler(RequestInfo info) override;
private:
	RequestResult error(const std::string& message);
	RequestResult signout(RequestInfo info);
	RequestResult getRooms(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo info);
	RequestResult getPersonalStats(RequestInfo info);
	RequestResult getHighScore(RequestInfo info);
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);
	int generateRoomID(std::string roomName);
	RequestHandlerFactory& m_handlerFactory;
	StatisticsManager& m_statisticsManager;
	RoomManager& m_roomManager;
	LoggedUser m_user;
};

