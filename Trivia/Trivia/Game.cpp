#include "Game.h"
#include "ExceptionHandler.h"

Game::Game(std::list<Question> questions, std::vector<std::string> users,int gameId)
{
	for (std::list<Question>::iterator it = questions.begin(); it != questions.end(); it++)
	{
		m_question.push_back(*it);
	}
	for (std::vector<std::string>::iterator it = users.begin(); it != users.end();it++)
	{
		GameData game = { m_question.front(),0,0,0 };
		LoggedUser u = LoggedUser(*it);
		m_players.insert({ u,game });
	}
	this->gameId = gameId;
}

Question Game::getQuestionForUser(LoggedUser user)
{
	for (std::map<LoggedUser, GameData>::iterator it = m_players.begin(); it != m_players.end(); it++)
	{
		LoggedUser u = it->first;
		if (u == user)
		{
			return it->second.currentQuestion;
		}
	}
	throw ExceptionHandler("Error, user not found in game");
}

void Game::submitAnswer(LoggedUser user, std::string answer)
{
	
	std::map<LoggedUser,GameData>::iterator it = m_players.find(user);
	if (it != m_players.end())
	{
		if (it->second.currentQuestion.getCorrectAnswer() == answer)
		{
			it->second.correctAnswerCount++;
		}
		else
		{
			it->second.wrongAnswerCount++;
		}
	}
	else
	{
		throw ExceptionHandler("Error, user not found in game");
	}
}

void Game::removePlayer(LoggedUser user)
{
	for (std::map<LoggedUser, GameData>::iterator it = m_players.begin(); it != m_players.end(); it++)
	{
		LoggedUser u = it->first;
		if (u == user)
		{
			m_players.erase(it);
			return;
		}
	}
	throw ExceptionHandler("Error, user not found in game");
}

std::map<LoggedUser, GameData>& Game::getGameResults()
{
	return m_players;
}
