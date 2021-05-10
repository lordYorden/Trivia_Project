#include "Server.h"
#define EXIT "EXIT"

/*
* Server class constractor
* input: ip - the ip of the server (std::string&)
*		,port - the port of which the server is listening for requests (int)
*		,database - the db of which the server is storing its data in (IDatabase*)
* output: none
*/
Server::Server(std::string& ip, int port, IDatabase* database):
	_ip(ip), _port(port), m_database(database), 
	m_hadlerFactory(RequestHandlerFactory(database)), m_communicator(Communicator(m_hadlerFactory))
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
