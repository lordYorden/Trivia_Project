#pragma once
#include <iostream>
#include <vector>
#include "json.hpp"
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
class JsonResponseSerializer
{
public:
	static std::vector<unsigned char> serializeLoginResponse(LoginResponse login);
	static std::vector<unsigned char> serializeSignupResponse(SignupResponse signUp);
	static std::vector<unsigned char> serializeErrorResponse(ErrorResponse Error);
};
