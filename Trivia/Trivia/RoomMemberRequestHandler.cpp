#include "RoomMemberRequestHandler.h"
#include "Helper.h"
#include "json.hpp"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"

/*
* The Constructor of Class RoomMemberRequestHandler
* input: factory - the factory handler (RequestHandlerFactory&)
*		,user - the user logged in (LoggedUser&)
*		,room - the room of which the user is in (Room&)
* output: none
*/
RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& factory, LoggedUser& user, Room& room):
	RoomRequestHandler(factory, user, room)
{
}

/*
* The Distructor of Class RoomMemberRequestHandler
* input: none
* output: none
*/
RoomMemberRequestHandler::~RoomMemberRequestHandler()
{
}

/*
* check if the request is part of the room Member requests
* input: info - the request information (RequestInfo)
* output: isRequestRelevent - if the request is part of the room Member requests (bool)
*/
bool RoomMemberRequestHandler::isRequestRelevent(RequestInfo info)
{
	return info.id == RequestId::MT_LEAVE_ROOM || info.id == MT_GET_ROOM_STATE;
}

/*
* handle the Member room requests from the client
* input: info - the request information (RequestInfo)
* output: requestRes - the request result to send back to client (RequestResult)
*/
RequestResult RoomMemberRequestHandler::RequestHandler(RequestInfo info)
{
	if (!isRequestRelevent(info))
	{
		std::string message = "Error!....Wait for start or leave Room to continue";
		return error(message);
	}

	try
	{
		switch (info.id)
		{
		case RequestId::MT_LEAVE_ROOM:
			return leaveRoom(info);
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
* the function handles the leaveRoom requests of the user
* input: info - the leaveRoom request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	int roomID = m_room.getMetadata().id;
	m_roomManager.getRoomById(m_room.getMetadata().id).removeUser(m_user);
	std::cout << "user " << m_user.getUsername() << " has left " << "room " << roomID << std::endl;
	LeaveRoomResponse leaveRes = { RequestId::MT_RESPONSE_OK };
	newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	buffer = JsonResponseSerializer::serializeLeaveRoomResponse(leaveRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}
