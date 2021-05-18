#pragma once
#include "IDatabase.h"
#include <vector>
#include <iostream>
#include <string>
class StatisticsManager
{
private:
	IDatabase* m_database;
public:
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);
};