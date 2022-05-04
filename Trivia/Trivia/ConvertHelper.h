#pragma once
#include<iostream>
#include<bitset>
#include <vector>
#include <string>
#include <algorithm>
#include "RoomManager.h"
#include "json.hpp"
class ConvertHelper
{
public:
	static std::string intToBin(int code);
	static std::string fillZeros(std::string binLength);
	static unsigned char byteTochar(std::string byte);
	static void fillingVector(std::vector<unsigned char>& buffer, nlohmann::json jpacket);
	static std::string roomDataToJsonStr(RoomData& metadata);

	
};