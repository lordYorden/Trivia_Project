#include "RoomRequestHandler.h"
#include "Helper.h"
#include "json.hpp"
#include "RequestHandlerFactory.h"

RoomRequestHandler::RoomRequestHandler(RequestHandlerFactory& factory, LoggedUser& user, Room& room):
	IRequestHandler(), m_handlerFactory(factory), m_roomManager(factory.getRoomManager()), m_room(room), m_user(user)
{
}

RoomRequestHandler::~RoomRequestHandler()
{
}

RequestResult RoomRequestHandler::getRoomState(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	RoomData metadata = m_room.getMetadata();
	GetRoomStateResponse stateRes = { RequestId::MT_RESPONSE_OK, metadata.isActive, m_room.getAllUsers(), metadata.numOfQuestionsInGame, metadata.timePerQuestion };
	std::cout << "sended data on room " << metadata.id << std::endl;
	buffer = JsonResponseSerializer::serializeGetRoomStateResponse(stateRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}
