#pragma once
#include "Networking.h"
#include "NetworkPlayerManager.h"

class NetworkHost
{
public:
	NetworkHost();
	~NetworkHost();
	// TODO: Host code here.

	Networking::NetPlayer player;

	bool Hosting();

private:
	sf::TcpListener hostListener;
	sf::TcpSocket hostSocket;
};

