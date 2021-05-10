#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include <iostream>
#include <string>
#include <thread>
#include "Helper.h"
#include <Ws2tcpip.h>
#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"

class Communicator
{
public:
	Communicator(RequestHandlerFactory& factory);
	~Communicator();
	void startHandleRequests(std::string ip, int port);
private:
	//connection thread
	void bindAndListen(const std::string& ip, int port);
	//client thread
	void handleNewClient(SOCKET clientSocket);
	//properties
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;
};