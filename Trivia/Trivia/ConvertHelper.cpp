#include "ConvertHelper.h"
#include <string>
#include <algorithm>
#include "json.hpp"
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
	for (int i = 0; i < 32 - binLength.length(); i++)
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
	std::string binCode = intToBin(size);
	binCode = fillZeros(binCode);
	int start = 0;
	for (int i = 0; i < 4; i++)
	{

		std::string newStr = binCode.substr(start, 8);
		buffer.push_back(byteTochar(newStr));
		start += 8;
		newStr = "";

	}
	for (int i = 0; i < size; i++)
	{
		buffer.push_back(j.dump()[i]);
	}
}

