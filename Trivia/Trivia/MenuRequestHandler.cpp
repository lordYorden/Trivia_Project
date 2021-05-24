#include "MenuRequestHandler.h"
#include "Helper.h"
#include "json.hpp"
#include "RequestHandlerFactory.h"
#define RANDOM_NUMBER 1.5

/*
* The Constructor of Class MenuRequestHandler
* input: factory - the factory handler (RequestHandlerFactory&)
*		,user - the user logged in (LoggedUser&)
* output: none
*/
MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& Factory, LoggedUser& user):
	IRequestHandler(), m_handlerFactory(Factory), m_roomManager(Factory.getRoomManager()), m_statisticsManager(Factory.getStatisticsManager()), m_user(user)
{
}

/*
* The Distructor of Class MenuRequestHandler
* input: none
* output: none
*/
MenuRequestHandler::~MenuRequestHandler()
{
}

/*
* check if the request is part of ther menu requests
* input: info - the request information (RequestInfo)
* output: isRequestRelevent - if the request is part of ther menu requests (bool)
*/
bool MenuRequestHandler::isRequestRelevent(RequestInfo info)
{
	return info.id == RequestId::MT_SIGNOUT_REQUEST || info.id == RequestId::MT_GET_ROOMS_REQUEST || info.id == RequestId::MT_GET_PLAYERS_IN_ROOM_REQUEST || info.id == RequestId::MT_GET_STATISTICS || info.id == RequestId::MT_JOIN_ROOM || info.id == RequestId::MT_CREATE_ROOM;
}

/*
* handle the menu requests from the client
* input: info - the request information (RequestInfo)
* output: requestRes - the request result to send back to client (RequestResult)
*/
RequestResult MenuRequestHandler::RequestHandler(RequestInfo info)
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
		case RequestId::MT_SIGNOUT_REQUEST:
			return signout(info);
		case RequestId::MT_GET_ROOMS_REQUEST:
			return getRooms(info);
		case RequestId::MT_GET_PLAYERS_IN_ROOM_REQUEST:
			return getPlayersInRoom(info);
		case RequestId::MT_GET_STATISTICS:
			return getStatistics(info);
		case RequestId::MT_JOIN_ROOM:
			return joinRoom(info);
		case RequestId::MT_CREATE_ROOM:
			return createRoom(info);
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

/*
* the function handles the signout process of the user
* input: info - the signout request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
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

/*
* the function handles the getRooms requests of the user
* input: info - the getRooms request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
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

/*
* the function handles the getPlayersInRooms requests of the user
* input: info - the getPlayersInRoom request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
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

/*
* the function handles the getStatistics requests of the user
* input: info - the getStatistics request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult MenuRequestHandler::getStatistics(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	std::vector<std::string> stats = m_statisticsManager.getUserStatistics(m_user.getUsername());
	std::vector<std::string> highScore = m_statisticsManager.getHighScore();
	GetStatisticsResponse statsRes = { RequestId::MT_RESPONSE_OK, highScore, stats};
	buffer = JsonResponseSerializer::serializeStatisticsResponse(statsRes);
	std::cout << "statistics for " << m_user.getUsername() << std::endl;
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

/*
* the function handles the joinRoom requests of the user
* input: info - the joinRoom request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
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

/*
* the function handles the createRoom requests of the user
* input: info - the createRoom request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	CreateRoomRequest createRoomReq = JsonRequestPacketDeserializer::deserializerCreateRoomRequest(info.buffer);
	int roomID = generateRoomID(createRoomReq.roomName);
	RoomData metadata = {roomID, createRoomReq.roomName, createRoomReq.maxUsers, createRoomReq.questionCount, createRoomReq.answerTimeOut, false};
	m_roomManager.createRoom(m_user, metadata);
	std::cout << m_user.getUsername() << "Has created Room " << roomID << "!" << std::endl;
	CreateRoomResponse createRoomRes = { RequestId::MT_RESPONSE_OK };
	buffer = JsonResponseSerializer::serializeCreateRoomResponse(createRoomRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

/*
* *helper method*
* generate the roomID given it`s name
* input: roomName - the room name (std::string)
* output: roomID - the room created (int)
*/
int MenuRequestHandler::generateRoomID(std::string roomName)
{
	time_t now = time(0);
	tm* localtm = localtime(&now);
	int timeFormula = localtm->tm_min + localtm->tm_hour;
	int len = roomName.length();
	return (timeFormula * len) / RANDOM_NUMBER;
}