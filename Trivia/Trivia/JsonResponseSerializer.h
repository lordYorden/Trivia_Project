#pragma once
#include <iostream>
#include <vector>
#include "json.hpp"
#include <map>
#include "RoomManager.h"
struct LoginResponse
{
	int status;
}typedef LoginResponse;
struct SignupResponse
{
	int status;
}typedef SignupResponse;
struct ErrorResponse
{
	std::string message;
}typedef ErrorResponse;
struct LogoutResponse
{
	unsigned int status;
}typedef LogoutResponse;
struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
}typedef GetRoomsResponse;

struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
}typedef GetPlayersInRoomResponse;

struct GetStatisticsResponse
{
	unsigned int status;
	
	std::vector<std::string> stats;

}typedef GetStatisticsResponse;
struct GetScoresResponse
{
	unsigned int status;
	std::vector<std::string> scores;
}typedef GetScoresResponse;
struct JoinRoomResponse
{
	unsigned int status;

}typedef JoinRoomResponse;
struct CreateRoomResponse
{
	unsigned int status;
}typedef CreateRoomResponse;

struct CloseRoomResponse
{
	unsigned int status;
}typedef CloseRoomResponse;

struct StartGameResponse
{
	unsigned int status;
}typedef StartGameResponse;

struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
}typedef GetRoomStateResponse;

struct LeaveRoomResponse
{
	unsigned int status;
}typedef LeaveRoomResponse;
struct LeaveGameResponse
{
	unsigned int status;
}typedef LeaveGameResponse;
struct GetQuestionResponse
{
	unsigned int status;
	std::string question;
	std::string correctAnswer;
	std::string otherAnswers;
	
}typedef GetQuestionResponse;
struct SubmitAnswerResponse
{
	unsigned int status;

}typedef SubmitAnswerResponse;
struct PlayerResults
{
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
	int score;

}typedef PlayerResults;
struct GetGameResultsResponse
{
	unsigned int status;
	std::vector<PlayerResults> results;

}typedef GetGameResultsResponse;


class JsonResponseSerializer
{
public:
	static std::vector<unsigned char> serializeLoginResponse(LoginResponse login);
	static std::vector<unsigned char> serializeSignupResponse(SignupResponse signUp);
	static std::vector<unsigned char> serializeErrorResponse(ErrorResponse Error);
	static std::vector<unsigned char> serializeLogoutResponse(LogoutResponse logout);
	static std::vector<unsigned char> serializeGetRoomsResponse(GetRoomsResponse rooms);
	static std::vector<unsigned char> serializeJoinRoomsResponse(JoinRoomResponse joinRoom);
	static std::vector<unsigned char> serializeGetPlayersInRoomResponse(GetPlayersInRoomResponse playersInRoom);
	static std::vector<unsigned char> serializeCreateRoomResponse(CreateRoomResponse createRoom);
	static std::vector<unsigned char> serializeStatisticsResponse(GetStatisticsResponse statistics);
	static std::vector<unsigned char> serializeHighScoresResponse(GetScoresResponse scores);
	static std::vector<unsigned char> serializeCloseRoomResponse(CloseRoomResponse response);
	static std::vector<unsigned char> serializeStartGameResponse(StartGameResponse response);
	static std::vector<unsigned char> serializeGetRoomStateResponse(GetRoomStateResponse response);
	static std::vector<unsigned char> serializeLeaveRoomResponse(LeaveRoomResponse response);
	static std::vector<unsigned char> serializeLeaveGameResponse(LeaveGameResponse response);
	static std::vector<unsigned char> serializeGetQuestionResponse(GetQuestionResponse response);
	static std::vector<unsigned char> serializeSubmitAnswerResponse(SubmitAnswerResponse response);
	static std::vector<unsigned char> serializeGetGameResultsResponse(GetGameResultsResponse response);
	
};
