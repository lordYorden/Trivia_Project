#include "Helper.h"
#define DATA_LEN 4
#define REQUEST_ID_LEN 1

/*
* orgenize the process of reciveing a message
* input: sock - socket connection (SOCKET)
* output: info - the request info from the user (RequestInfo)
*/
RequestInfo Helper::getUserRequestInfo(SOCKET sock)
{
	int requestId = getRequestId(sock);
	int bufferLen = getIntPartFromSocket(sock, DATA_LEN);
	std::time_t currTime = std::time(nullptr);
	std::vector<unsigned char> buffer = getBufferFromSocket(sock, bufferLen);
	RequestInfo info = { requestId, currTime, buffer };
	return info;
}

/*
* orgenize the process of reciveing a message
* input: sock - socket connection (SOCKET)
* output: info - the request info from the user (RequestInfo)
*/
int Helper::getRequestId(SOCKET sock)
{
	char* s = getPartFromSocket(sock, REQUEST_ID_LEN);
	std::string msg(s);

	if (msg == "")
		return 0;

	int res = std::atoi(s);
	delete s;
	return  res;
}

// recieve data from socket according byteSize
// this is private function
char* Helper::getPartFromSocket(SOCKET sc, int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}

char* Helper::getPartFromSocket(SOCKET sc, int bytesNum, int flags)
{
	if (bytesNum == 0)
	{
		return (char*)"";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}

	data[bytesNum] = 0;
	return data;
}

// recieve data from socket according byteSize
// returns the data as int
int Helper::getIntPartFromSocket(SOCKET sc, int bytesNum)
{
	char* s = getPartFromSocket(sc, bytesNum, 0);
	return atoi(s);
}

/*
* gets the message from the user and puts it in std::vector<unsigned char>
* input: sc - socket connection (SOCKET)
*		,bytesNum - the length of the message (int)
* output: buffer - the user message (std::vector<unsigned char>)
*/
std::vector<unsigned char> Helper::getBufferFromSocket(SOCKET sc, int bytesNum)
{
	char* s = getPartFromSocket(sc, bytesNum, 0);
	std::vector<unsigned char> res;
	for (int i = 0; i < bytesNum; i++)
	{
		res.push_back(s[i]);
	}
	return res;
}

/*
* sends the given message to the user 
* input: sc - socket connection (SOCKET)
*		,message - the message to user (std::vector<unsigned char>)
* output: none
*/
void Helper::sendData(SOCKET sock, std::vector<unsigned char> message)
{
	unsigned char* data = message.data();

	if (send(sock, (const char*)data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

// return string after padding zeros if necessary
std::string Helper::getPaddedNumber(int num, int digits)
{
	std::ostringstream ostr;
	ostr << std::setw(digits) << std::setfill('0') << num;
	return ostr.str();

}