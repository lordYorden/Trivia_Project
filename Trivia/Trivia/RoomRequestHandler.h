#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponseSerializer.h"

class RequestHandlerFactory;
class RoomRequestHandler : public IRequestHandler
{
public:
	RoomRequestHandler(RequestHandlerFactory& factory, LoggedUser& user, Room& room);
	~RoomRequestHandler();
	virtual bool isRequestRelevent(RequestInfo info) = 0;
	virtual RequestResult RequestHandler(RequestInfo info) = 0;
protected:
	RequestResult getRoomState(RequestInfo info);
	RequestHandlerFactory& m_handlerFactory;
	RoomManager& m_roomManager;
	Room& m_room;
	LoggedUser m_user;
};

