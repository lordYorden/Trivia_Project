#include "LoginRequestHandler.h"
#include "Helper.h"

/*
* empty LoginRequestHandler class constractor
* input: none
* output: none
*/
LoginRequestHandler::LoginRequestHandler():
	IRequestHandler()
{
}

/*
* empty LoginRequestHandler class distractor
* input: none
* output: none
*/
LoginRequestHandler::~LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevent(RequestInfo info)
{
	return info.id == RequestId::MT_LOGIN_REQUEST || info.id == RequestId::MT_SIGNUP_REQUEST;
}

RequestResult LoginRequestHandler::RequestHandler(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	if (!isRequestRelevent(info))
	{
		ErrorResponse errorRes;
		errorRes.message = "Error!....Signup or Login before continue";
		buffer = JsonResponseSerializer::serializeErrorResponse(errorRes);
		RequestResult RequestRes = { buffer, newHandler };
		return RequestRes;
	}
	
	try
	{
		if (info.id == RequestId::MT_LOGIN_REQUEST)
		{
			LoginRequest userInfo = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
			std::cout << "username: " << userInfo.username << ", password: " << userInfo.password << std::endl;
			LoginResponse logRes;
			logRes.status = RequestId::MT_RESPONSE_OK;
			buffer = JsonResponseSerializer::serializeLoginResponse(logRes);
			std::cout << "Login Successful" << std::endl;
		}
		else
		{
			SignupRequest userInfo = JsonRequestPacketDeserializer::deserializerSignupRequest(info.buffer);
			std::cout << "username: " << userInfo.username << ", password: " << userInfo.password << ", email: " << userInfo.email << std::endl;
			SignupResponse signRes;
			signRes.status = RequestId::MT_RESPONSE_OK;
			buffer = JsonResponseSerializer::serializeSignupResponse(signRes);
			std::cout << "Signup Successful" << std::endl;
		}
	}
	catch (std::exception& e)
	{
		ErrorResponse errorRes;
		errorRes.message = "Error!....Invalid Json";
		buffer = JsonResponseSerializer::serializeErrorResponse(errorRes);
	}

	RequestResult RequestRes = { buffer, newHandler };
	return RequestRes;
}
