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
    std::string roomsStr = "";
    buffer.push_back(RequestId::MT_RESPONSE_OK + TO_CHAR);
    nlohmann::json j;
    j["status"] = rooms.status;
    for (std::vector<RoomData>::iterator it = rooms.rooms.begin(); it != rooms.rooms.end(); it++)
    {
        roomsStr += (it->name + ", ");
    }
    roomsStr = roomsStr.substr(0, roomsStr.length() - 2);
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
        players += *it + ", ";

    }
    players = players.substr(0, players.length() - 2);
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
        stats += *it + ", ";
    }

    stats = stats.substr(0, stats.length() - 2);
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
        highscores += *it + "&";
    }
    highscores = highscores.substr(0, highscores.length() - 2);
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

std::vector<unsigned char> JsonResponseSerializer::serializeJoinRoomResponse(StartGameResponse response)
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
        players += *it + ",";
    }
    players = players.substr(0, players.length() - 2);
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

