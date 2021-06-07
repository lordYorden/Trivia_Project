#include "JsonResponseSerializer.h"
#include "ConvertHelper.h"
#include "Helper.h"
#define TO_CHAR 48

std::vector<unsigned char> JsonResponseSerializer::serializeLoginResponse(LoginResponse login)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = login.status;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeSignupResponse(SignupResponse signUp)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = signUp.status;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeErrorResponse(ErrorResponse Error)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(RequestId::MT_ERROR + TO_CHAR);
    nlohmann::json j;
    j["message"] = Error.message;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeLogoutResponse(LogoutResponse logout)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = logout.status;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeGetRoomsResponse(GetRoomsResponse rooms)
{
    std::vector<unsigned char> buffer;
    std::string roomsStr = "[";
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = rooms.status;
    for (std::vector<RoomData>::iterator it = rooms.rooms.begin(); it != rooms.rooms.end(); it++)
    {
        roomsStr += ConvertHelper::roomDataToJsonStr(*it);
        if (it + 1 != rooms.rooms.end())
        {
            roomsStr += "-";
        }
    }
    roomsStr += "]";
    std::cout << roomsStr << std::endl;
    /*roomsStr = roomsStr.substr(0, roomsStr.length() - 1);*/
    j["Rooms"] = roomsStr;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;

}

std::vector<unsigned char> JsonResponseSerializer::serializeJoinRoomsResponse(JoinRoomResponse joinRoom)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = joinRoom.status;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;

}

std::vector<unsigned char> JsonResponseSerializer::serializeGetPlayersInRoomResponse(GetPlayersInRoomResponse playersInRoom)
{
    std::vector<unsigned char> buffer;
    std::string players = "";
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    for (std::vector<std::string>::iterator it = playersInRoom.players.begin(); it != playersInRoom.players.end(); it++)
    {
        players += *it + "-";

    }
    players = players.substr(0, players.length() - 1);
    j["Players"] = players;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeCreateRoomResponse(CreateRoomResponse createRoom)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = createRoom.status;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeStatisticsResponse(GetStatisticsResponse statistics)
{
    std::vector<unsigned char> buffer;
    std::string stats = "";
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = statistics.status;
    for (std::vector<std::string>::iterator it = statistics.stats.begin(); it != statistics.stats.end(); it++)
    {
        stats += *it + "-";
    }

    stats = stats.substr(0, stats.length() - 1);
    j["Statistics"] = stats;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
    
}

std::vector<unsigned char> JsonResponseSerializer::serializeHighScoresResponse(GetScoresResponse scores)
{
    std::vector<unsigned char> buffer;
    std::string stats = "";
    std::string highscores = "";
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = scores.status;
    
    for (std::vector<std::string>::iterator it = scores.scores.begin(); it != scores.scores.end(); it++)
    {
        highscores += *it + "-";
    }
    highscores = highscores.substr(0, highscores.length() - 1);
    j["Highscores"] = highscores;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeCloseRoomResponse(CloseRoomResponse response)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = response.status;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeStartGameResponse(StartGameResponse response)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = response.status;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeGetRoomStateResponse(GetRoomStateResponse response)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = response.status;
    j["hasGameBegun"] = response.hasGameBegun;
    j["questionCount"] = response.questionCount;
    j["answerTimeout"] = response.answerTimeout;
    std::string players = "";
    for (std::vector<std::string>::iterator it = response.players.begin(); it != response.players.end(); it++)
    {
        players += *it + "-";
    }
    players = players.substr(0, players.length() - 1);
    j["players"] = players;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;

}

std::vector<unsigned char> JsonResponseSerializer::serializeLeaveRoomResponse(LeaveRoomResponse response)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = response.status;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeLeaveGameResponse(LeaveGameResponse response)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = response.status;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeGetQuestionResponse(GetQuestionResponse response)
{
    std::string answers = "";
    std::vector<unsigned char> buffer;
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = response.status;
    j["question"] = response.question;
    j["correctAnswer"] = response.correctAnswer;
    j["otherAnswers"] = response.otherAnswers;
    
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeSubmitAnswerResponse(SubmitAnswerResponse response)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = response.status;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeGetGameResultsResponse(GetGameResultsResponse response)
{
    std::string results = "";
    std::vector<unsigned char> buffer;
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = response.status;
    if (response.status == 0)
        j["results"] = "";
    else
    {
        for (std::vector<PlayerResults>::iterator it = response.results.begin(); it != response.results.end(); it++)
        {
            results += (it->username + "&" + std::to_string(it->correctAnswerCount) + "&" + std::to_string(it->wrongAnswerCount) +"&"+ std::to_string(it->averageAnswerTime)+"&"+std::to_string(it->score) + "-");
        }
        results = results.substr(0, results.length() - 1);
        j["results"] = results;
    }
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
    
}

