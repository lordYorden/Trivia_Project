#pragma once
#include <ctime>
#include <vector>

class IRequestHandler;

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
	//abstruct methods to override in base class
	virtual bool isRequestRelevent(RequestInfo info) = 0;
	virtual RequestResult RequestHandler(RequestInfo info) = 0;

private:

};