#include "SqliteDatabase.h"
#include "sqlite3.h"
#include "Question.h"
#include <iostream>
#include <exception>
#include "ExceptionHandler.h"
#include <list>
#include <string>
void SqliteDatabase::open()
{
	std::string dbFileName = "UserDB.sqlite";
	int res = sqlite3_open(dbFileName.c_str(), &_db);
	if (res != SQLITE_OK) {
		_db = NULL;
		std::cout << "Failed to open DB" << std::endl;
	}
	std::cout << "opend" << std::endl;
	std::string statement = "CREATE TABLE IF NOT EXISTS USERS(UNAME TEXT NOT NULL PRIMARY KEY,PASSWORD TEXT NOT NULL,MAIL TEXT NOT NULL);";
	ExecuteSQL(statement);
	std::string statement1 = "CREATE TABLE IF NOT EXISTS QUESTIONS(QID INTEGER PRIMARY KEY AUTOINCREMENT,QUESTION TEXT NOT NULL,CorrectAns TEXT NOT NULL,ANS2 TEXT NOT NULL, ANS3 TEXT NOT NULL, ANS4 TEXT NOT NULL);";
	ExecuteSQL(statement1);
	std::string statement4 = "CREATE TABLE IF NOT EXISTS GAME(GAMEID INTEGER PRIMARY KEY);";
	ExecuteSQL(statement4);
	std::string statement3 = "CREATE TABLE IF NOT EXISTS STATISTIC(GAMEID INTEGER NOT NULL,UNAME TEXT NOT NULL,ISCORRECT INTEGER,ANSWERTIME INTEGER NOT NULL,SCORE INTEGER NOT NULL);";
	ExecuteSQL(statement3);
	std::cout << "Opened both tables" << std::endl;
}

std::vector<std::string> SqliteDatabase::getTopFiveScores()
{
	std::vector<std::string> scores;
	std::string statement = "SELECT UNAME,SUM(SCORE) SCORESUM FROM STATISTIC GROUP BY UNAME ORDER BY SCORESUM DESC LIMIT 5;";
	ExecuteSqlCallback(statement, fillScoreCallback, &scores);
	return scores;
}

void SqliteDatabase::insertIntoStatistics(int gameId, std::string username, std::string answer, int answerTime)
{
	std::string statement = "INSERT INTO STATISTIC(GAMEID,UNAME,ISCORRECT,ANSWERTIME,SCORE)\ VALUES(" + std::to_string(gameId) + ",\"" + username + "\"," + std::to_string(isAnswerCorrect(answer)) + "," + std::to_string(answerTime) + "," + std::to_string(1000 * isAnswerCorrect(answer) - (answerTime / 100.0) * 1000 * isAnswerCorrect(answer)) + ");";
	ExecuteSQL(statement);
}

int SqliteDatabase::isAnswerCorrect(std::string answer)
{
	bool flag = false;
	std::string statement = "SELECT * FROM QUESTIONS WHERE CorrectAns = \"" + answer + "\";";
	ExecuteSqlCallback(statement, isExistsCallback, &flag);
	return flag ? 1 : 0;
	
}

void SqliteDatabase::insertGame(int gameId)
{
	std::string statement = "INSERT INTO GAME(GAMEID) VALUES(" + std::to_string(gameId) + ");";
	ExecuteSQL(statement);

}

int SqliteDatabase::getPlayerScore(int gameId, std::string uname)
{
	int score = 0;
	std::string statement = "SELECT SUM(SCORE) WHERE UNAME = \"" + uname + "\" AND GAMEID = " + std::to_string(gameId) + ";";
	ExecuteSqlCallback(statement, getIntCallback, &score);
	return score;
	
}


void SqliteDatabase::ExecuteSQL(std::string statement)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->_db, statement.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << "Failed SQL" << std::endl;
		return;
	}
	return;
}


bool SqliteDatabase::doesUserExist(std::string name)
{
	bool flag = false;
	std::string statement = "SELECT * FROM USERS\ WHERE UNAME = \"" + name + "\";";
	ExecuteSqlCallback(statement, isExistsCallback, &flag);
	return flag;

}

bool SqliteDatabase::doesPasswordMatch(std::string name, std::string password)
{
	bool flag = false;
	std::string statement = "SELECT * FROM USERS\ WHERE UNAME = \"" + name + "\" AND PASSWORD = \"" + password + "\";";
	ExecuteSqlCallback(statement, isExistsCallback, &flag);
	return flag;
}

void SqliteDatabase::addNewUser(std::string name, std::string password, std::string mail)
{
	std::string statement = "INSERT INTO USERS(UNAME,PASSWORD,MAIL)\ VALUES(\"" + name + "\",\"" + password + "\",\"" + mail + "\");";
	ExecuteSQL(statement);
}

std::list<Question> SqliteDatabase::getQuestions(int num)
{
	std::list<Question> q;
	std::string statement = "SELECT * FROM QUESTIONS LIMIT " + std::to_string(num) + ";";
	ExecuteSqlCallback(statement, fillQuestionsCallback, &q);
	return q;
}

float SqliteDatabase::getAverageAnswerTime(std::string name)
{
	float time = 0;
	std::string statement = "SELECT AVG(ANSWERTIME) FROM STATISTIC WHERE UNAME = \"" + name + "\";";
	try
	{
		ExecuteSqlCallback(statement, getFloatCallback, &time);
	}
	catch (std::exception& e)
	{
		throw ExceptionHandler("Error...User wasn't found");
	}
	
	return time;
}

int SqliteDatabase::getNumOfCorrectAnswers(std::string name)
{
	int num = 0;
	std::string statement = "SELECT COUNT(UNAME) FROM STATISTIC\ WHERE UNAME = \"" + name + "\" AND ISCORRECT = 1;";
	ExecuteSqlCallback(statement, getIntCallback, &num);
	return num;

}

int SqliteDatabase::getNumOfTotalAnswers(std::string name)
{
	int num = 0;
	std::string statement = "SELECT COUNT(UNAME) FROM STATISTIC WHERE UNAME = \""+name+"\";";
	ExecuteSqlCallback(statement, getIntCallback, &num);
	return num;
}

int SqliteDatabase::getNumOfPlayerGames(std::string name)
{
	int num = 0;
	std::string statement = "SELECT COUNT(DISTINCT GAMEID) FROM STATISTIC WHERE UNAME = \"" + name + "\";";
	ExecuteSqlCallback(statement, getIntCallback, &num);
	return num;
}

void SqliteDatabase::ExecuteSqlCallback(std::string statement, int(*callback)(void*, int, char**, char**), void* data)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->_db, statement.c_str(), callback, data, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << "Failed SQL" << std::endl;
		return;
	}

	return;
}
int SqliteDatabase::isExistsCallback(void* data, int argc, char** argv, char** azColName)
{
	*(bool*)data = true;
	return 0;
}

int SqliteDatabase::fillQuestionsCallback(void* data, int argc, char** argv, char** azColName)
{
	Question q = Question(argv[1], argv[2], argv[3], argv[4], argv[5]);
	((std::list<Question>*)data)->push_back(q);
	return 0;
}

int SqliteDatabase::getFloatCallback(void* data, int argc, char** argv, char** azColName)
{
	try
	{
		if(argv[0] != nullptr)
			*(float*)data = std::stof(argv[0]);
	}
	catch (std::exception& e)
	{
		throw ExceptionHandler("Error...User wasn't found");
	}
	return 0;
}

int SqliteDatabase::getIntCallback(void* data, int argc, char** argv, char** azColName)
{
	if (argv[0] != nullptr)	
		*(int*)data = atoi(argv[0]);
	return 0;
}

int SqliteDatabase::fillScoreCallback(void* data, int argc, char** argv, char** azColName)
{
	std::string str1 = std::string(argv[0]);
	std::string str2 = std::string(argv[1]);
	(*(std::vector<std::string>*)data).push_back(str1+"="+str2);
	return 0;

}
