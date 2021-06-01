#include "LoginRequestHandler.h"
#include "Helper.h"
#include "json.hpp"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"

/*
* LoginRequestHandler class constractor
* input: factory - the Request Handler Factory (RequestHandlerFactory&)
* output: none
*/
LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& factory):
	IRequestHandler(), m_handlerFactory(factory), m_loginManager(factory.getLoginManager())
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

/*
* check if the request is a login or signup request
* input: info - the request information (RequestInfo)
* output: isRequestRelevent - if the request is a login or signup request (bool)
*/
bool LoginRequestHandler::isRequestRelevent(RequestInfo info)
{
	return info.id == RequestId::MT_LOGIN_REQUEST || info.id == RequestId::MT_SIGNUP_REQUEST;
}

/*
* handle the login request from the client
* input: info - the request information (RequestInfo)
* output: requestRes - the request result to send back to client (RequestResult)
*/
RequestResult LoginRequestHandler::RequestHandler(RequestInfo info)
{
	if (!isRequestRelevent(info))
	{
		std::string message = "Error!....Signup or Login before continue";
		return error(message);
	}
	
	try
	{
		if (info.id == RequestId::MT_LOGIN_REQUEST)
		{
			return login(info);
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
* the function handles the login process of a user
* input: info - the login request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult LoginRequestHandler::login(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	LoginRequest userInfo = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
	std::cout << "username: " << userInfo.username << ", password: " << userInfo.password << std::endl;
	m_loginManager.login(userInfo.username, userInfo.password);
	LoginResponse logRes;
	logRes.status = RequestId::MT_RESPONSE_OK;
	buffer = JsonResponseSerializer::serializeLoginResponse(logRes);
	std::cout << "Login Successful" << std::endl;
	LoggedUser user = LoggedUser(userInfo.username);
	newHandler = m_handlerFactory.createMenuRequestHandler(user);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

/*
* the function handles the signup process of a user
* input: info - the signup request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult LoginRequestHandler::signup(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	SignupRequest userInfo = JsonRequestPacketDeserializer::deserializerSignupRequest(info.buffer);
	std::cout << "username: " << userInfo.username << ", password: " << userInfo.password << ", email: " << userInfo.email << std::endl;
	m_loginManager.signup(userInfo.username, userInfo.password, userInfo.email);
	SignupResponse signRes;
	signRes.status = RequestId::MT_RESPONSE_OK;
	buffer = JsonResponseSerializer::serializeSignupResponse(signRes);
	std::cout << "Signup Successful" << std::endl;
	LoggedUser user = LoggedUser(userInfo.username);
	newHandler = m_handlerFactory.createMenuRequestHandler(user);
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
RequestResult LoginRequestHandler::error(const std::string& message)
{
	ErrorResponse errorRes;
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	errorRes.message = message;
	buffer = JsonResponseSerializer::serializeErrorResponse(errorRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}
