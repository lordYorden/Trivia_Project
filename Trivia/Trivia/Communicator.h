#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include <iostream>
#include <string>
#include <thread>

class Communicator
{
public:
	Communicator();
	~Communicator();
	void startHandleRequests();
private:
	//connection thread
	void bindAndListen();
	//client thread
	void handleNewClient(SOCKET clientSocket);
	//properties
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler> m_clients;
};