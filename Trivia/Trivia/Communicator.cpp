#include "Communicator.h"
#define RECIVED_MESSGAE_SIZE 6
#define NULL 0

/*
* init the socket connection to a tcp socket
* input: factory - the Request Handler Factory (RequestHandlerFactory&)
* output: none
*/
Communicator::Communicator(RequestHandlerFactory& factory, std::mutex& mutex):
	m_handlerFactory(factory), m_locker(mutex)
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

/*
	closes the socket and all aloctaed memmory at the end
	of the server program
	input: none
	output: none
*/
Communicator::~Communicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(m_serverSocket);
	}
	catch (...) {}
}

/*
	the main connection thread 
	input: none
	output: none
*/
void Communicator::startHandleRequests(std::string ip, int port)
{
	bindAndListen(ip, port);
}


/*
* the connection thread that listen in the agreed port 
* to new users and creates a thread for them
* input: none
* output: none
*/
void Communicator::bindAndListen(const std::string& ip, int port)
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	inet_pton(AF_INET, ip.c_str(), &sa.sin_addr.s_addr); //ip addres from user

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		// notice that we step out to the global namespace
		// for the resolution of the function accept

		// this accepts the client and create a specific socket from server to this client
		SOCKET client_socket = ::accept(m_serverSocket, NULL, NULL);

		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		std::cout << "Client accepted. Server and client can speak" << std::endl;

		// the function that handle the conversation with the client
		//create a thread of the function that handle the conversation with the client

		LoginRequestHandler* clientHandler = m_handlerFactory.createLoginRequestHandler();
		m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, clientHandler));
		std::thread t = std::thread(&Communicator::handleNewClient, this, client_socket);
		t.detach();
	}
}

/*
* the main client thread that manages every client
* input: clientSocket - the tcp connection to the client (SOCKET)
* output: none
*/
void Communicator::handleNewClient(SOCKET clientSocket)
{
	try
	{
		IRequestHandler* handler = m_clients[clientSocket];
		RequestInfo reqInfo;
		RequestResult reqRes;
		std::vector<unsigned char> buffer;
		do
		{
			reqInfo = Helper::getUserRequestInfo(clientSocket);
			m_locker.lock();
			reqRes = handler->RequestHandler(reqInfo);
			if (reqRes.newHandler != nullptr)
			{
				handler = reqRes.newHandler;
			}
			buffer = reqRes.responseBuffer;
			Helper::sendData(clientSocket, buffer);
			m_locker.unlock();
		} while (reqInfo.id != RequestId::MT_EXIT);

		closesocket(clientSocket);
		std::cout << "client has disconnected!" << std::endl;

	}
	catch (const std::exception& e)
	{
		closesocket(clientSocket);
		std::cout << "client has disconnected!" << std::endl;
	}
}
