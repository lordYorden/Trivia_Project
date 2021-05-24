#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* database):
    m_database(database)
{
}

StatisticsManager::~StatisticsManager()
{
}

std::vector<std::string> StatisticsManager::getHighScore()
{
    return m_database->getTopFiveScores();
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
    std::vector<std::string> stats;
    stats.push_back(std::to_string(m_database->getAverageAnswerTime(username)));
    stats.push_back(std::to_string(m_database->getNumOfCorrectAnswers(username)));
    stats.push_back(std::to_string(m_database->getNumOfTotalAnswers(username)));
    stats.push_back(std::to_string(m_database->getNumOfPlayerGames(username)));
    return stats;
}
