#include "JsonRequestPacketDeserializer.h"
#include <bitset>
#include <sstream>
#include <string>
#include "json.hpp"

/*
* static function
* the function gets a json in the form of a binery message and return 
* the user login contact details in the form of a struct
* input: buffer - the json binery message (std::vector<unsigend char>&)
* output: info - the user login details (struct LoginRequest)
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char>& buffer)
{
    std::string jsonStr = BinToStr(buffer);
    //after convertion
    auto j = nlohmann::json::parse(jsonStr);
    std::string username = j.at("username");
    std::string password = j.at("password");

    LoginRequest info = { username, password };
    return info;
}

/*
* static function
* the function gets a json in the form of a binery message and return
* the user signup contact details in the form of a struct
* input: buffer - the json binery message (std::vector<unsigend char>&)
* output: info - the user signup details (struct SignupRequest)
*/
SignupRequest JsonRequestPacketDeserializer::deserializerSignupRequest(std::vector<unsigned char>& buffer)
{
    std::string jsonStr = BinToStr(buffer);
    //after convertion
    auto j = nlohmann::json::parse(jsonStr);
    std::string username = j.at("username");
    std::string password = j.at("password");
    std::string mail = j.at("mail");

    SignupRequest info = { username, password, mail };
    return info;
}

/*
* static function
* the function gets a json in the form of a binery message and return
* the room details to check the players in room
* input: buffer - the json binery message (std::vector<unsigend char>&)
* output: info - room details (struct GetPlayersInRoomRequest)
*/
GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializerGetPlayersRequest(std::vector<unsigned char>& buffer)
{
    std::string jsonStr = BinToStr(buffer);
    //after convertion
    auto j = nlohmann::json::parse(jsonStr);
    unsigned int roomID = j.at("roomID");

    GetPlayersInRoomRequest info = { roomID };
    return info;
}

/*
* static function
* the function gets a json in the form of a binery message and return
* the room details to join in
* input: buffer - the json binery message (std::vector<unsigend char>&)
* output: info - room details (struct JoinRoomRequest)
*/
JoinRoomRequest JsonRequestPacketDeserializer::deserializerJoinRoomRequest(std::vector<unsigned char>& buffer)
{
    std::string jsonStr = BinToStr(buffer);
    //after convertion
    auto j = nlohmann::json::parse(jsonStr);
    unsigned int roomID = j.at("roomID");

    JoinRoomRequest info = { roomID };
    return info;
}

/*
* static function
* the function gets a json in the form of a binery message and return
* the room creation details
* input: buffer - the json binery message (std::vector<unsigend char>&)
* output: info - room creation details (struct CreateRoomRequest)
*/
CreateRoomRequest JsonRequestPacketDeserializer::deserializerCreateRoomRequest(std::vector<unsigned char>& buffer)
{
    std::string jsonStr = BinToStr(buffer);
    //after convertion
    auto j = nlohmann::json::parse(jsonStr);
    std::string roomName = j.at("roomName");
    unsigned int maxUsers = j.at("maxUsers");
    unsigned int questionCount = j.at("questionCount");
    unsigned int answerTimeout = j.at("answerTimeout");

    CreateRoomRequest info = { roomName, maxUsers, questionCount, answerTimeout };
    return info;
}

/*
* static function
* the function gets a json in the form of a binery message and return
* the submit answer details
* input: buffer - the json binery message (std::vector<unsigend char>&)
* output: info - submit answer details (struct SubmitAnswerRequest)
*/
SubmitAnswerRequest JsonRequestPacketDeserializer::deserializerSubmitAnswerRequest(std::vector<unsigned char>& buffer)
{
    std::string jsonStr = BinToStr(buffer);
    //after convertion
    auto j = nlohmann::json::parse(jsonStr);
    int answerID = j.at("answerID");
    SubmitAnswerRequest info = { answerID };
    return info;
}

/*
* helper method 
* get a binery message a and returns it as an std::string
* input: buffer - binery message (std::vector<unsigend char>&)
* output: jsonStr - decoded message (std::string)
*/
std::string JsonRequestPacketDeserializer::BinToStr(std::vector<unsigned char>& buffer)
{
    std::string jsonStr = "";
    for (auto it = buffer.begin(); it != buffer.end(); it++)
    {
        jsonStr += (char)*it;
    }
    return jsonStr;
}


