#pragma once
#include <iostream>
#include <string>
#include <list>
#include <SFML/Network.hpp>
#include <map>

class Networking
{
public:
	Networking();
	~Networking();

	struct NetPlayer
	{
		float dataHeader;

		float id;
		std::string name;
		std::string color;
		float ping;
		
		float xPosition;
		float yPosition;
	};

	friend sf::Packet& operator <<(sf::Packet& packet, const Networking::NetPlayer& player)
	{
		return packet << player.dataHeader << player.id << player.name << player.color << player.ping << player.xPosition << player.yPosition;
	}

	friend sf::Packet& operator >>(sf::Packet& packet, Networking::NetPlayer& player)
	{
		return packet >> player.dataHeader >> player.id >> player.name >> player.color >> player.ping >> player.xPosition >> player.yPosition;
	}
};

