#include "GameManager.h"
#include <algorithm>
Game GameManager::CreateGame(Room room)
{
	std::list<Question> q = m_database->getQuestions(room.getMetadata().numOfQuestionsInGame);
	std::vector<std::string> players = room.getAllUsers();
	Game g = Game(q, players, room.getMetadata().id);
	m_games.push_back(g);
	m_database->insertGame(g.getGameId());
	return g;
}

void GameManager::deleteGame(Game game)
{
	for (std::vector<Game>::iterator it = m_games.begin(); it != m_games.end(); it++)
	{
		if (game.getGameId() == it->getGameId())
		{
			m_games.erase(it);
			return;
		}
	}
}

void GameManager::submitAnswer(Game game,LoggedUser user, std::string answer,int answerTime)
{
	m_database->insertIntoStatistics(game.getGameId(), user.getUsername(), answer, answerTime);
	game.submitAnswer(user, answer);
}

std::map<LoggedUser, GameData>& GameManager::getGameResults(Game game)
{
	return game.getGameResults();
}
