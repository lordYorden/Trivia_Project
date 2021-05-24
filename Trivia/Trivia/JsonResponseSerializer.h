#pragma once
#include <iostream>
#include <vector>
#include "json.hpp"
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
struct GetHighScoresResponse
{
	unsigned int status;
	std::vector<std::string>scores;
}typedef GetHighScoresResponse;
struct JoinRoomResponse
{
	unsigned int status;

}typedef JoinRoomResponse;
struct CreateRoomResponse
{
	unsigned int status;
}typedef CreateRoomResponse;

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
	static std::vector<unsigned char> serializeHighScoresResponse(GetHighScoresResponse statistics);

};
