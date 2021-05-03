#pragma once
#include <ctime>
#include "Helper.h"
#include <vector>

typedef struct RequestInfo
{
	int id;
	std::time_t recivedTime;
	std::vector<unsigned char> buffer;
}RequestInfo;

typedef struct RequestResult
{
	std::vector<unsigned char> responseBuffer;
	IRequestHandler* newHandler;
}RequestResult;

class IRequestHandler
{
public:
	IRequestHandler();
	~IRequestHandler();
	virtual bool isRequestRelevent(RequestInfo info) = 0;
	virtual RequestResult RequestHandler(RequestInfo info) = 0;

private:

};