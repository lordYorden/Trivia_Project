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

class Game
{
private:
	std::vector<Question> m_question;
	std::map<LoggedUser, GameData> m_players;
	int gameId;
public:
	Game(std::list<Question> questions, std::vector<std::string> users, int gameId);
	Game(int gameId);
	Question getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, std::string answer);
	void removePlayer(LoggedUser user);
	bool operator==(Game const& other) const;
	std::map<LoggedUser, GameData>& getGameResults();
	int getGameId()
	{
		return this->gameId;
	}


};