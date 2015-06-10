#pragma once
#include "Networking.h"
#include "NetworkPlayerManager.h"
#include <sstream>

class NetworkHost
{
public:
	NetworkHost();
	~NetworkHost();
	// TODO: Host code here.
	bool Hosting();

private:
	sf::Clock m_clock;
	sf::Time m_endTime;

	float m_timeDelta;
};

