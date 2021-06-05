#pragma once
#include "RoomRequestHandler.h"
#include "RoomManager.h"
#include "IRequestHandler.h"
#include "RoomRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponseSerializer.h"

class RequestHandlerFactory;
class RoomMemberRequestHandler : public RoomRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory& factory, LoggedUser& user, Room& room);
	~RoomMemberRequestHandler();
	virtual bool isRequestRelevent(RequestInfo info) override;
	virtual RequestResult RequestHandler(RequestInfo info) override;
private:
	RequestResult leaveRoom(RequestInfo info);
};

