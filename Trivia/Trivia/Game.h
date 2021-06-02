#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "IDatabase.h"
#include "LoggedUser.h"
#include "Question.h"
struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
};
bool operator<(const LoggedUser& n1, const LoggedUser& n2)
{
	
	LoggedUser p1 = n1;
	LoggedUser p2 = n2;
	return p1.getUsername().length() < p2.getUsername().length();
}
class Game
{
private:
	std::vector<Question> m_question;
	std::map<LoggedUser, GameData> m_players;
public:
	Game(std::list<Question> questions, std::vector<std::string> users);
	void getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, std::string answer);
	void removePlayer(LoggedUser user);

};