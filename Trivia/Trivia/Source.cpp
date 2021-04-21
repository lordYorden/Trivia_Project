#pragma comment (lib, "ws2_32.lib")
#define PORT 200
#include "Server.h"
#include "WSAInitializer.h"

int main() 
{
	WSAInitializer wsaInit;
	std::string ip = "127.0.0.1";
	Server myServer(ip, PORT);
	//runs the server
	try
	{
		myServer.run();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	return 0;
}