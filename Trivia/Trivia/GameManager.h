#pragma once
#include "IDatabase.h";
#include "Game.h"
#include <vector>
#include <list>
#include <map>
#include "RoomManager.h"
#include "JsonResponseSerializer.h"
class GameManager
{
private:
	IDatabase* m_database;
	std::vector<Game> m_games;
public:
	GameManager(IDatabase* database);
	Game& CreateGame(Room room);
	void deleteGame(Game game);
	void submitAnswer(Game game,LoggedUser user, std::string answer, int answerTime);
	Game& getGameByID(int gameID, LoggedUser& user);
	std::vector<PlayerResults>& getGameResults(Game game);
	

};