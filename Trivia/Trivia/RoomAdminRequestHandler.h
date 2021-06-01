#pragma once
#include "RoomManager.h"
#include "IRequestHandler.h"
#include "RoomRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponseSerializer.h"

class RequestHandlerFactory;
class RoomAdminRequestHandler : public RoomRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& factory, LoggedUser& user, Room& room);
	~RoomAdminRequestHandler();
	virtual bool isRequestRelevent(RequestInfo info) override;
	virtual RequestResult RequestHandler(RequestInfo info) override;
private:
	RequestResult error(const std::string& message);
	RequestResult closeRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
};