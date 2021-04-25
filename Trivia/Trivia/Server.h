#pragma once
#include "Communicator.h"

class Server
{
public:
	Server(std::string& ip, int port);
	~Server();
	//runs the server components
	void run();

private:
	Communicator m_communicator;
	std::string _ip;
	int _port;
};