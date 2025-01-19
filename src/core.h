#pragma once

#include "WebSocket.h"
#include <string>
#include <iostream>


class Core {
private:
	WebSocket m_coreWebSocket;
	char* readMessageBuf[65536]; 
	// listener
	// chat history
	// commands (ie maybe !<something> is an OS command...)
	// state (comms connected etc)
	// Core should pass messages to websocket to send. 
	// Websocket should listen for and pass back responses
	//

public:
	Core()  = default;
	~Core() = default;
	void sendMessage();
	bool checkForMessage();
};
