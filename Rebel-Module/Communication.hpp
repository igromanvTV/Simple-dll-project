#pragma once

#pragma comment(lib, "ws2_32.lib")
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <thread>

#include "Execution.hpp"

class CCommunication
{
private:
	SOCKET server_socket, client_socket;
	struct sockaddr_in client = {};
	struct sockaddr_in server = {};
	WSADATA wsa;
public:
	bool InitializeScriptServer(int port);
	std::string ReceiveScript();
};
