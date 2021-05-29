#pragma once
#include "RoomManager.h"
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponseSerializer.h"

class RequestHandlerFactory;
class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& Factory, LoggedUser& user, Room& room);
	~RoomAdminRequestHandler();
	virtual bool isRequestRelevent(RequestInfo info) override;
	virtual RequestResult RequestHandler(RequestInfo info) override;
private:
	RequestResult error(const std::string& message);
	RequestResult closeRoom(RequestInfo info);
	/*RequestResult startGame(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);*/

	RequestHandlerFactory& m_handlerFactory;
	RoomManager& m_roomManager;
	Room m_room;
	LoggedUser m_user;
};