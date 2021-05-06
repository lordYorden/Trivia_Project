#pragma once
#include "IRequestHandler.h"
#include "JsonResponseSerializer.h"
#include "JsonRequestPacketDeserializer.h"

class LoginRequestHandler : public IRequestHandler 
{
public:
	LoginRequestHandler();
	~LoginRequestHandler();
	virtual bool isRequestRelevent(RequestInfo info) override;
	virtual RequestResult RequestHandler(RequestInfo info) override;
private:

};