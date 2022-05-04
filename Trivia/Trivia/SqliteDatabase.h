#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <list>
#include <vector>
class SqliteDatabase : public IDatabase
{
public:
	bool doesUserExist(std::string name) override;
	bool doesPasswordMatch(std::string name, std::string password)override;
	void addNewUser(std::string name, std::string password, std::string mail)override;
	
	std::list<Question> getQuestions(int num)override;
	float getAverageAnswerTime(std::string name)override;
	int getNumOfCorrectAnswers(std::string name)override;
	int getNumOfTotalAnswers(std::string name)override;
	int getNumOfPlayerGames(std::string name)override;
	void ExecuteSQL(std::string statement);
	void ExecuteSqlCallback(std::string statement, int(*callback)(void*, int, char**, char**), void* data);
	void open();
	std::vector<std::string> getTopFiveScores()override;
	void insertIntoStatistics(int gameId, std::string username, std::string answer, int answerTime)override;
	int isAnswerCorrect(std::string answer)override;
	 void insertGame(int gameId)override;
	 int getPlayerScore(int gameId, std::string uname)override;
	 void insertQuestion(std::string q, std::string correct, std::string ans2, std::string ans3, std::string ans4)override;
	 bool doesQuestionExist(std::string q)override;
private:

	static int isExistsCallback(void* data, int argc, char** argv, char** azColName);
	static int fillQuestionsCallback(void* data, int argc, char** argv, char** azColName);
	static int getFloatCallback(void* data, int argc, char** argv, char** azColName);
	static int getIntCallback(void* data, int argc, char** argv, char** azColName);
	static int fillScoreCallback(void* data, int argc, char** argv, char** azColName);
	sqlite3* _db;

};