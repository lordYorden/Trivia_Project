#pragma once
#include "IRequestHandler.h"
#include "JsonResponseSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "LoginManager.h"

class RequestHandlerFactory;
class LoginRequestHandler : public IRequestHandler 
{
public:
	LoginRequestHandler(RequestHandlerFactory& Factory);
	~LoginRequestHandler();
	virtual bool isRequestRelevent(RequestInfo info) override;
	virtual RequestResult RequestHandler(RequestInfo info) override;
private:
	RequestResult login(RequestInfo info);
	RequestResult signup(RequestInfo info);
	RequestResult error(const std::string& message);
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
};