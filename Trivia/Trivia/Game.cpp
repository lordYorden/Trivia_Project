#include "Game.h"

Game::Game(std::list<Question> questions, std::vector<std::string> users)
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
}

void Game::getQuestionForUser(LoggedUser user)
{
	for (std::map<LoggedUser, GameData>::iterator it = m_players.begin(); it != m_players.end(); it++)
	{
		LoggedUser u = it->first;
		if (u == user)
		{
			for (std::vector<Question>::iterator it1 = m_question.begin(); it1 != m_question.end(); it1++)
			{
				if (it1->getQuestion() == it->second.currentQuestion.getQuestion())
				{
					it->second.currentQuestion = *(it1 + 1);
				}
			}
		}
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
}
