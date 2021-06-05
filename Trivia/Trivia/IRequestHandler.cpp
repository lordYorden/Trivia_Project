#include "IRequestHandler.h"

/*
* empty IRequestHandler class constractor
* input: none
* output: none
*/
IRequestHandler::IRequestHandler()
{
}

/*
* empty IRequestHandler class distractor
* input: none
* output: none
*/
IRequestHandler::~IRequestHandler()
{
}

/*
  *helper method*
* the function get a message and return a RequestResult object to send
* to the user
* input: message - the error message (std::string)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult IRequestHandler::error(const std::string& message)
{
	ErrorResponse errorRes;
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	errorRes.message = message;
	buffer = JsonResponseSerializer::serializeErrorResponse(errorRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}
