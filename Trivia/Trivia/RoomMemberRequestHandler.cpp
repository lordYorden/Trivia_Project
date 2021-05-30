#include "RoomMemberRequestHandler.h"
#include "Helper.h"
#include "json.hpp"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& factory, LoggedUser& user, Room& room):
	RoomRequestHandler(factory, user, room)
{
}

RoomMemberRequestHandler::~RoomMemberRequestHandler()
{
}

bool RoomMemberRequestHandler::isRequestRelevent(RequestInfo info)
{
	return info.id == RequestId::MT_LEAVE_ROOM || info.id == MT_GET_ROOM_STATE;
}

RequestResult RoomMemberRequestHandler::RequestHandler(RequestInfo info)
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

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	int roomID = m_room.getMetadata().id;
	m_room.removeUser(m_user.getUsername());
	std::cout << "user " << m_user.getUsername() << "has left " << "room " << roomID << std::endl;
	LeaveRoomResponse leaveRes = { RequestId::MT_RESPONSE_OK };
	newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	buffer = JsonResponseSerializer::serializeLeaveRoomResponse(leaveRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

/*
  *helper method*
* the function get a message and return a RequestResult object to send
* to the user
* input: message - the error message (std::string)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult RoomMemberRequestHandler::error(const std::string& message)
{
	ErrorResponse errorRes;
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	errorRes.message = message;
	buffer = JsonResponseSerializer::serializeErrorResponse(errorRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}
