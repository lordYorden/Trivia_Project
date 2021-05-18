#include "MenuRequestHandler.h"
#include "Helper.h"
#include "json.hpp"
#include "RequestHandlerFactory.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& Factory, LoggedUser& User):
	m_handlerFactory(Factory), m_roomManager(Factory.getRoomManager()), m_statisticsManager(Factory.getStatisticsManager()), m_user(User)
{
}

MenuRequestHandler::~MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequestRelevent(RequestInfo info)
{
	return info.id == RequestId::MT_SIGNOUT_REQUEST || info.id == RequestId::MT_GET_ROOMS_REQUEST || info.id == RequestId::MT_GET_PLAYERS_IN_ROOM_REQUEST || info.id == RequestId::MT_GET_STATISTICS || info.id == RequestId::MT_JOIN_ROOM || info.id == RequestId::MT_CREATE_ROOM;
}

RequestResult MenuRequestHandler::RequestHandler(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	RequestResult* requestRes = nullptr;

	if (!isRequestRelevent(info))
	{
		std::string message = "Error!....Signup or Login before continue";
		return error(message);
	}

	try
	{
		if (info.id == RequestId::MT_SIGNOUT_REQUEST)
		{
			return signout(info);
		}
		else
		{
			return signup(info);
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
RequestResult MenuRequestHandler::error(const std::string& message)
{
	ErrorResponse errorRes;
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	errorRes.message = message;
	buffer = JsonResponseSerializer::serializeErrorResponse(errorRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

RequestResult MenuRequestHandler::signout(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	LoginManager loginManager = m_handlerFactory.getLoginManager();
	loginManager.logout(m_user.getUsername());
	std::cout << "Logout Successful" << std::endl;
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	std::vector<RoomData> rooms = m_roomManager.getRooms();
	std::cout << "Recived Rooms" << std::endl;
	GetRoomsResponse roomsRes  = {RequestId::MT_RESPONSE_OK, rooms};
	buffer = JsonResponseSerializer::serializeGetRoomsResponse(roomsRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	GetPlayersInRoomRequest getPlayersReq = JsonRequestPacketDeserializer::deserializerGetPlayersRequest(info.buffer);
	std::cout << "Room ID: " << getPlayersReq.roomID << std::endl;
	Room room = m_roomManager.getRoomById(getPlayersReq.roomID);
	std::vector<std::string> players = room.getAllUsers();
	GetPlayersInRoomResponse playersRes = {players};
	buffer = JsonResponseSerializer::serializeGetPlayersInRoomResponse(playersRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	JoinRoomRequest joinRoomReq = JsonRequestPacketDeserializer::deserializerJoinRoomRequest(info.buffer);
	std::cout << "Room ID: " << joinRoomReq.roomID << std::endl;
	Room room = m_roomManager.getRoomById(joinRoomReq.roomID);
	room.addUser(m_user);
	std::cout << "Room ID: " << joinRoomReq.roomID << std::endl;
	JoinRoomResponse joinRes = {RequestId::MT_RESPONSE_OK};
	buffer = JsonResponseSerializer::serializeJoinRoomsResponse(joinRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}
