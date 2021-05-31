#include "ConvertHelper.h"
#include <string>
#include <algorithm>
#include "json.hpp"
#include "Helper.h"
std::string ConvertHelper::intToBin(int code)
{
	std::string binCode = "";
	for (int i = 0; code > 0; i++)
	{
		binCode += std::to_string(code % 2);
		code = code / 2;
	}
	std::reverse(binCode.begin(), binCode.end());
	return binCode;

}

std::string ConvertHelper::fillZeros(std::string binLength)
{
	std::string zeroToFill = "";
	for (int i = 0; i < 4 - binLength.length(); i++)
	{
		zeroToFill += "0";
	}
	return zeroToFill + binLength;
}

unsigned char ConvertHelper::byteTochar(std::string byte)
{
	int sum = 0;
	for (int i = 0; i < byte.length(); i++)
	{
		if (byte[i] == '1')
		{
			sum += pow(2, byte.length() - i - 1);
		}

	}
	return (unsigned char)sum;
}

void ConvertHelper::fillingVector(std::vector<unsigned char>& buffer, nlohmann::json j)
{

	int size = j.dump().length();
	std::string binCode = std::to_string(size);
	binCode = fillZeros(binCode);
	int start = 0;
	for (int i = 0; i < 4; i++)
	{
		buffer.push_back(binCode[i]);
	}
	for (int i = 0; i < size; i++)
	{
		buffer.push_back(j.dump()[i]);
	}
}

std::string ConvertHelper::roomDataToJsonStr(RoomData& metadata)
{
	nlohmann::json j;
	j["name"] = metadata.name;
	j["id"] = metadata.id;
	return j.dump();
}

