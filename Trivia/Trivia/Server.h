#pragma once
#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "IDatabase.h"

class Server
{
public:
	Server(std::string& ip, int port, IDatabase* database);
	~Server();
	//runs the server components
	void run();

private:
	Communicator m_communicator;
	std::string _ip;
	int _port;
	RequestHandlerFactory m_hadlerFactory;
	IDatabase* m_database;
	std::mutex m_locker;
};