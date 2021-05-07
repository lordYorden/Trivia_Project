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
