#include "GameManager.h"
#include <algorithm>


GameManager::GameManager(IDatabase* database)
{
	m_database = database;
}

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

std::vector<PlayerResults>& GameManager::getGameResults(Game game)
{
	std::vector<PlayerResults> vec;
	for (std::map<LoggedUser, GameData>::iterator it = game.getGameResults().begin(); it != game.getGameResults().end(); it++)
	{
		LoggedUser l = it->first;
		PlayerResults p = { l.getUsername(),it->second.correctAnswerCount,it->second.wrongAnswerCount,it->second.averageAnswerTime };
		vec.push_back(p);
	}
	return vec;
}
