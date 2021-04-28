#include "JsonResponseSerializer.h"
#include "ConvertHelper.h"

std::vector<unsigned char> JsonResponseSerializer::serializeLoginResponse(LoginResponse login)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(ConvertHelper::byteTochar(ConvertHelper::intToBin(1)));
    nlohmann::json j;
    j["status"] = login.status;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeSignupResponse(SignupResponse signUp)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(ConvertHelper::byteTochar(ConvertHelper::intToBin(1)));
    nlohmann::json j;
    j["status"] = signUp.status;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}

std::vector<unsigned char> JsonResponseSerializer::serializeErrorResponse(ErrorResponse Error)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(ConvertHelper::byteTochar(ConvertHelper::intToBin(0)));
    nlohmann::json j;
    j["message"] = Error.message;
    ConvertHelper::fillingVector(buffer, j);
    return buffer;
}
