#include "RoomAdminRequestHandler.h"
#include "Helper.h"
#include "json.hpp"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"

/*
* The Constructor of Class RoomAdminRequestHandler
* input: factory - the factory handler (RequestHandlerFactory&)
*		,user - the user logged in (LoggedUser&)
*		,room - the room of which the user is in (Room&)
* output: none
*/
RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& Factory, LoggedUser& user, Room& room):
	IRequestHandler(), m_handlerFactory(Factory), m_roomManager(Factory.getRoomManager()), m_room(room), m_user(user)
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

bool RoomAdminRequestHandler::isRequestRelevent(RequestInfo info)
{
	return info.id == RequestId::MT_CLOSE_ROOM || info.id == RequestId::MT_START_GAME || info.id == RequestId::MT_GET_ROOM_STATE;
}

RequestResult RoomAdminRequestHandler::RequestHandler(RequestInfo info)
{
	if (!isRequestRelevent(info))
	{
		std::string message = "Error!....Signup or Login before continue";
		return error(message);
	}

	try
	{
		switch (info.id)
		{
		case RequestId::MT_CLOSE_ROOM:
			return closeRoom(info);
		/*case RequestId::MT_START_GAME:
			return startGame(info);
		case RequestId::MT_GET_ROOM_STATE:
			return getRoomState(info);*/
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
  *helper method*
* the function get a message and return a RequestResult object to send
* to the user
* input: message - the error message (std::string)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult RoomAdminRequestHandler::error(const std::string& message)
{
	ErrorResponse errorRes;
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	errorRes.message = message;
	buffer = JsonResponseSerializer::serializeErrorResponse(errorRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	int roomID = m_room.getMetadata().id;
	m_roomManager.deleteRoom(roomID);
	CloseRoomResponse closeRes = { RequestId::MT_RESPONSE_OK };
	std::cout << "the room " << roomID << " has been closed";
	newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}