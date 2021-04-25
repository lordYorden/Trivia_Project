#pragma comment (lib, "ws2_32.lib")
#define PORT 200
#define CONFIG_FILE_NAME "config.txt"
#define IP_ADDRESS_CUT 10
#define PORT_CUT 5
#include "Server.h"
#include "WSAInitializer.h"
#include <string>
#include <iostream>
#include <fstream>

int main() 
{
	WSAInitializer wsaInit;

	//gets the ip and port from config
	std::string ip = "";
	std::string port = "";

	std::ifstream file(CONFIG_FILE_NAME);
	if (file.is_open())
	{
		std::getline(file, ip);
		std::getline(file, port);

		ip = ip.substr(IP_ADDRESS_CUT, ip.length());
		port = port.substr(PORT_CUT, port.length());

		file.close();
	}

	Server myServer(ip, stoi(port));

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