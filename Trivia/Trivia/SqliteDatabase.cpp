#include "SqliteDatabase.h"
#include "sqlite3.h"
#include "Question.h"
#include <iostream>
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
	std::string statement4 = "CREATE TABLE IF NOT EXISTS GAMES(GAMEID INTEGER PRIMARY KEY,START TEXT NOT NULL,END TEXT NOT NULL);";
	ExecuteSQL(statement4);
	std::string statement3 = "CREATE TABLE IF NOT EXISTS STATISTIC(GAMEID INTEGER PRIMARY KEY,UNAME TEXT NOT NULL,ISCORRECT INTEGER,ANSWERTIME INTEGER NOT NULL,SCORE INTEGER NOT NULL, FOREIGN KEY(UNAME) REFERENCES USERS(UNAME), FOREIGN KEY(GAMEID) REFERENCES GAMES(GAMEID));";
	ExecuteSQL(statement3);
	std::cout << "Opened both tables" << std::endl;
}

std::vector<std::string> SqliteDatabase::getTopFiveScores()
{
	std::vector<std::string> scores;
	std::string statement = "SELECT * FROM STATISTIC ORDER BY SCORE DESC LIMIT 5;";
	ExecuteSqlCallback(statement, fillScoreCallback, &scores);
	return scores;
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
	std::string statement = "SELECT * FROM QUESTION LIMIT " + std::to_string(num) + ";";
	ExecuteSqlCallback(statement, fillQuestionsCallback, &q);
	return q;
}

float SqliteDatabase::getAverageAnswerTime(std::string name)
{
	float time = 0;
	std::string statement = "SELECT AVG(ANSWERTIME) FROM STATISTIC\ WHERE UNAME = \"" + name + "\";";
	ExecuteSqlCallback(statement, getFloatCallback, &time);
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
	std::string statement = "SELECT COUNT(UNAME) FROM STATISTIC;";
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
	Question q = Question(azColName[0], azColName[1], azColName[2], azColName[3], azColName[4]);
	(*(std::list<Question>*)data).push_back(q);
	return 0;
}

int SqliteDatabase::getFloatCallback(void* data, int argc, char** argv, char** azColName)
{
	*(float*)data = std::stof(azColName[0]);
	return 0;
}

int SqliteDatabase::getIntCallback(void* data, int argc, char** argv, char** azColName)
{
	*(int*)data = atoi(azColName[0]);
	return 0;
}

int SqliteDatabase::fillScoreCallback(void* data, int argc, char** argv, char** azColName)
{
	(*(std::vector<std::string>*)data).push_back(azColName[0]);
	return 0;
}
