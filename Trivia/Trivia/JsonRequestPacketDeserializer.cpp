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


