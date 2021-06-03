#pragma once
#include "IDatabase.h";
#include "Game.h"
#include <vector>
#include <list>
#include <map>
#include "RoomManager.h"
class GameManager
{
private:
	IDatabase* m_database;
	std::vector<Game> m_games;
public:
	Game CreateGame(Room room);
	void deleteGame(Game game);
	void submitAnswer(Game game,LoggedUser user, std::string answer, int answerTime);
	std::map<LoggedUser, GameData>& getGameResults(Game game);
	

};