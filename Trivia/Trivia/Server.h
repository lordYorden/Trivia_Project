#pragma once
#include "Communicator.h"

class Server
{
public:
	Server();
	~Server();
	//runs the server components
	void run();

private:
	Communicator m_communicator;
};