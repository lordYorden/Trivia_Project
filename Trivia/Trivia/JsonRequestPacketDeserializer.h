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

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char>& buffer);
	static SignupRequest deserializerSignupRequest(std::vector<unsigned char>& buffer);

private:
	static std::string BinToStr(std::vector<unsigned char>& buffer);
};