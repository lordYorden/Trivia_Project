#pragma once
#include "IRequestHandler.h"
#include <string>
#include <iostream>
#include <vector>
#include <WinSock2.h>
#include <Windows.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>

enum RequestId
{
	MT_RESPONSE_OK = 0,
	MT_LOGIN_REQUEST = 1,
	MT_SIGNUP_REQUEST = 2,
	MT_SIGNOUT_REQUEST = 3,
	MT_GET_ROOMS_REQUEST = 4,
	MT_GET_PLAYERS_IN_ROOM_REQUEST = 5,
	MT_GET_STATISTICS = 6,
	MT_GET_HIGHSCORES = 7,
	MT_JOIN_ROOM = 8,
	MT_CREATE_ROOM = 9,
	MT_CLOSE_ROOM = 10,
	MT_START_GAME = 11,
	MT_LEAVE_ROOM = 12,
	MT_GET_ROOM_STATE = 13,
	MT_LEAVE_GAME_REQUEST = 14,
	MT_GET_QUESTION_REQUEST = 15,
	MT_SUBMIT_ANSWER_REQUEST = 16,
	MT_GET_GAME_RESULT_REQUEST = 17,
	MT_EXIT = 99,
	MT_ERROR = 1
};

class Helper
{
public:
	static RequestInfo getUserRequestInfo(SOCKET sock);
	static int getRequestId(SOCKET sock);
	static int getIntPartFromSocket(SOCKET sc, int bytesNum);
	static std::vector<unsigned char> getBufferFromSocket(SOCKET sc, int bytesNum);
	static void sendData(SOCKET sock, std::vector<unsigned char> message);



private:
	static char* getPartFromSocket(SOCKET sc, int bytesNum);
	static char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);
	static std::string getPaddedNumber(int num, int digits);
};