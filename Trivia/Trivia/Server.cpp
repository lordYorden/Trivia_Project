#include "Server.h"

/*
* empty server class constractor
* input: none
* output: none
*/
Server::Server()
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
* runs the server components
* input: none
* output: none
*/
void Server::run()
{
	m_communicator.startHandleRequests();
}
