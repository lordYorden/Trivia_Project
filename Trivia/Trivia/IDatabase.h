#pragma once
#include <iostream>
#include "Question.h"
#include <list>
#include <vector>
class IDatabase
{
public:
	virtual bool doesUserExist(std::string name) = 0;
	virtual bool doesPasswordMatch(std::string name, std::string password) = 0;
	virtual void addNewUser(std::string name, std::string password, std::string mail) = 0;
	virtual std::list<Question> getQuestions(int num) = 0;
	virtual float getAverageAnswerTime(std::string name) = 0;
	virtual int getNumOfCorrectAnswers(std::string name) = 0;
	virtual int getNumOfTotalAnswers(std::string name) = 0;
	virtual int getNumOfPlayerGames(std::string name) = 0;
	virtual std::vector<std::string> getTopFiveScores() = 0;
	

};