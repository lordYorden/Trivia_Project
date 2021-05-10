#pragma once
#include <iostream>
class IDatabase
{
public:
	virtual bool doesUserExist(std::string name) = 0;
	virtual bool doesPasswordMatch(std::string name, std::string password) = 0;
	virtual void addNewUser(std::string name, std::string password, std::string mail) = 0;

};