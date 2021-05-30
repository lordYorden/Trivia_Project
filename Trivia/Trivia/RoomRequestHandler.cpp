#include "RoomRequestHandler.h"
#include "Helper.h"
#include "json.hpp"
#include "RequestHandlerFactory.h"

/*
* The Constructor of Class RoomRequestHandler
* input: factory - the factory handler (RequestHandlerFactory&)
*		,user - the user logged in (LoggedUser&)
*		,room - the room of which the user is in (Room&)
* output: none
*/
RoomRequestHandler::RoomRequestHandler(RequestHandlerFactory& factory, LoggedUser& user, Room& room):
	IRequestHandler(), m_handlerFactory(factory), m_roomManager(factory.getRoomManager()), m_room(room), m_user(user)
{
}

/*
* The Distructor of Class RoomRequestHandler
* input: none
* output: none
*/
RoomRequestHandler::~RoomRequestHandler()
{
}

/*
* the function handles the getRoomState requests of the user
* input: info - the getRoomState request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
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