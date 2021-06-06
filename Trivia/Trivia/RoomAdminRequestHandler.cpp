#include "RoomAdminRequestHandler.h"
#include "Helper.h"
#include "json.hpp"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#include "GameRequestHandler.h"

/*
* The Constructor of Class RoomAdminRequestHandler
* input: factory - the factory handler (RequestHandlerFactory&)
*		,user - the user logged in (LoggedUser&)
*		,room - the room of which the user is in (Room&)
* output: none
*/
RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& factory, LoggedUser& user, Room& room):
	RoomRequestHandler(factory, user, room)
{
}

/*
* The Distructor of Class RoomAdminRequestHandler
* input: none
* output: none
*/
RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
}

/*
* check if the request is part of the room Admin requests
* input: info - the request information (RequestInfo)
* output: isRequestRelevent - if the request is part of the room Admin requests (bool)
*/
bool RoomAdminRequestHandler::isRequestRelevent(RequestInfo info)
{
	return info.id == RequestId::MT_CLOSE_ROOM || info.id == RequestId::MT_START_GAME || info.id == RequestId::MT_GET_ROOM_STATE;
}

/*
* handle the Admin room requests from the client
* input: info - the request information (RequestInfo)
* output: requestRes - the request result to send back to client (RequestResult)
*/
RequestResult RoomAdminRequestHandler::RequestHandler(RequestInfo info)
{
	if (!isRequestRelevent(info))
	{
		std::string message = "Error!....Start or Close Room to continue";
		return error(message);
	}

	try
	{
		switch (info.id)
		{
		case RequestId::MT_CLOSE_ROOM:
			return closeRoom(info);
		case RequestId::MT_START_GAME:
			return startGame(info);
		case RequestId::MT_GET_ROOM_STATE:
			return getRoomState(info);
		}
	}
	catch (nlohmann::json::parse_error& e)
	{
		std::string message = "Error!....Invalid Json";
		return error(message);
	}
	catch (ExceptionHandler& e)
	{
		std::string message = e.what();
		std::cout << message << std::endl;
		return error(message);
	}
}

/*
* the function handles the closeRoom requests of the user
* input: info - the closeRoom request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	int roomID = m_room.getMetadata().id;
	m_roomManager.deleteRoom(roomID);
	CloseRoomResponse closeRes = { RequestId::MT_RESPONSE_OK };
	std::cout << "the room " << roomID << " has been closed" << std::endl;
	newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	buffer = JsonResponseSerializer::serializeCloseRoomResponse(closeRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

/*
* the function handles the startGame requests of the user
* input: info - the startGame request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	int roomID = m_room.getMetadata().id;
	m_roomManager.getRoomById(roomID).setRoomState(true);
	Game& game = m_handlerFactory.getGameManager().CreateGame(m_room);
	newHandler = m_handlerFactory.createGameRequestHandler(game, m_user);
	std::cout << "the room " << roomID << " has started the game" << std::endl;
	StartGameResponse startRes = { RequestId::MT_RESPONSE_OK };
	buffer = JsonResponseSerializer::serializeStartGameResponse(startRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}
