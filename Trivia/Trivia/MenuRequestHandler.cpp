#include "MenuRequestHandler.h"
#include "Helper.h"
#include "json.hpp"
#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
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
* check if the request is part of the menu requests
* input: info - the request information (RequestInfo)
* output: isRequestRelevent - if the request is part of ther menu requests (bool)
*/
bool MenuRequestHandler::isRequestRelevent(RequestInfo info)
{
	return info.id == RequestId::MT_SIGNOUT_REQUEST || info.id == RequestId::MT_GET_ROOMS_REQUEST || info.id == RequestId::MT_GET_PLAYERS_IN_ROOM || info.id == RequestId::MT_GET_STATISTICS || info.id == RequestId::MT_GET_HIGHSCORES || info.id == RequestId::MT_JOIN_ROOM || info.id == RequestId::MT_CREATE_ROOM || info.id == RequestId::MT_ADD_QUESTION;
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
		std::string message = "Error!....You have to pick an option";
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
		case RequestId::MT_GET_PLAYERS_IN_ROOM:
			return getPlayersInRoom(info);
		case RequestId::MT_GET_STATISTICS:
			return getPersonalStats(info);
		case RequestId::MT_GET_HIGHSCORES:
			return getHighScore(info);
		case RequestId::MT_JOIN_ROOM:
			return joinRoom(info);
		case RequestId::MT_CREATE_ROOM:
			return createRoom(info);
		case RequestId::MT_ADD_QUESTION:
			return addQuestion(info);
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
* the function handles the signout process of the user
* input: info - the signout request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult MenuRequestHandler::signout(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	LoginManager& loginManager = m_handlerFactory.getLoginManager();
	loginManager.logout(m_user.getUsername());
	std::cout << "Logout Successful" << std::endl;
	newHandler = m_handlerFactory.createLoginRequestHandler();
	LogoutResponse logoutRes = { RequestId::MT_RESPONSE_OK };
	buffer = JsonResponseSerializer::serializeLogoutResponse(logoutRes);
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
RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	std::vector<std::string> stats = m_statisticsManager.getUserStatistics(m_user.getUsername());
	GetStatisticsResponse statsRes = { RequestId::MT_RESPONSE_OK, stats};
	buffer = JsonResponseSerializer::serializeStatisticsResponse(statsRes);
	std::cout << "statistics for " << m_user.getUsername() << std::endl;
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

/*
* the function handles the getHighScore requests of the user
* input: info - the getHighScore request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult MenuRequestHandler::getHighScore(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	std::vector<std::string> highScores = m_statisticsManager.getHighScore();
	GetScoresResponse highScoreRes = { RequestId::MT_RESPONSE_OK, highScores};
	buffer = JsonResponseSerializer::serializeHighScoresResponse(highScoreRes);
	std::cout << "high score for " << m_user.getUsername() << std::endl;
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
	Room& room = m_roomManager.getRoomById(joinRoomReq.roomID);
	room.addUser(m_user);
	std::cout << "Room ID: " << joinRoomReq.roomID << std::endl;
	JoinRoomResponse joinRes = {RequestId::MT_RESPONSE_OK};
	buffer = JsonResponseSerializer::serializeJoinRoomsResponse(joinRes);
	newHandler = m_handlerFactory.createRoomMemberRequestHandler(joinRoomReq.roomID, m_user);
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
	std::cout << m_user.getUsername() << " Has created Room " << roomID << "!" << std::endl;
	CreateRoomResponse createRoomRes = { roomID};
	buffer = JsonResponseSerializer::serializeCreateRoomResponse(createRoomRes);
	newHandler = m_handlerFactory.createRoomAdminRequestHandler(roomID, m_user);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

/*
* the function handles the Add Question requests of the user
* input: info - the Add Question request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult MenuRequestHandler::addQuestion(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	SubmitQuestionRequest submitQuestionReq = JsonRequestPacketDeserializer::deserializerSubmitQuestionRequest(info.buffer);
	m_statisticsManager.insertQuestion(submitQuestionReq.question, submitQuestionReq.correctAns, submitQuestionReq.secAns, submitQuestionReq.thirdAns, submitQuestionReq.fourthAns);
	
		std::cout << m_user.getUsername() << " Has submited a question!" << std::endl;
		GetSubmitAnswerResponse res = { 1 };
		buffer = JsonResponseSerializer::serializeGetSubmitAnswerResponse(res);
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
