#pragma comment (lib, "ws2_32.lib")

#include "Server.h"
#include "WSAInitializer.h"

int main() 
{
	WSAInitializer wsaInit;
	Server myServer;
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