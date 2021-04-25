#include "Server.h"
#define EXIT "EXIT"

/*
* empty server class constractor
* input: none
* output: none
*/
Server::Server(std::string& ip, int port):
	_ip(ip), _port(port)
{
}

/*
* empty server class distractor
* input: none
* output: none
*/
Server::~Server()
{
}

/*
* runs the server components and checks if 
* the user wants to exit the program
* input: none
* output: none
*/
void Server::run()
{
	std::thread t = std::thread(&Communicator::startHandleRequests, this->m_communicator, _ip, _port);
	t.detach();
	std::string message = "";
	do
	{
		std::getline(std::cin, message);
	} while (message != EXIT);
}
