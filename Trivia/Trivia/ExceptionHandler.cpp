#include "ExceptionHandler.h"

/*
* ExceptionHandler class constructor 
* input: message - the error message (std::string)
* output: none
*/
ExceptionHandler::ExceptionHandler(std::string message):
	_errorMessage(message)
{
}

/*
* ExceptionHandler class distructor
* input: none
* output: none
*/
ExceptionHandler::~ExceptionHandler()
{
}

/*
* the exception itself
* input: none
* output: none
*/
char const* ExceptionHandler::what() const noexcept
{
	return _errorMessage.c_str();
}
