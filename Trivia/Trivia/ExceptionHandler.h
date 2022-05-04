#pragma once
#include <exception>
#include <iostream>
class ExceptionHandler : public std::exception
{
public:
	ExceptionHandler(std::string message);
	~ExceptionHandler();
	virtual char const* what() const noexcept;
private:
	std::string _errorMessage;
};

