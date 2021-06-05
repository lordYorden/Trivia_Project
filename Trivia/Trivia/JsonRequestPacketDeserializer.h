#pragma once
#include <iostream>
#include <vector>

typedef struct LoginRequest
{
	std::string username;
	std::string password;

}LoginRequest;

typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;

}SignupRequest;

typedef struct GetPlayersInRoomRequest
{
	unsigned int roomID;

}GetPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomID;

}JoinRoomRequest;

typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeOut;

}CreateRoomRequest;
typedef struct SubmitAnswerRequest {
	std::string answer;
	int answerTime;
}SubmitAnswerRequest;

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char>& buffer);
	static SignupRequest deserializerSignupRequest(std::vector<unsigned char>& buffer);
	static GetPlayersInRoomRequest deserializerGetPlayersRequest(std::vector<unsigned char>& buffer);
	static JoinRoomRequest deserializerJoinRoomRequest(std::vector<unsigned char>& buffer);
	static CreateRoomRequest deserializerCreateRoomRequest(std::vector<unsigned char>& buffer);
	static SubmitAnswerRequest deserializerSubmitAnswerRequest(std::vector<unsigned char>& buffer);

private:
	static std::string BinToStr(std::vector<unsigned char>& buffer);
};