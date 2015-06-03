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
		float id;
		std::string name;
		std::string color;
		float ping;

		bool isReady;
		bool isWinner;
		
		float xPosition;
		float yPosition;
	};

	friend sf::Packet& operator <<(sf::Packet& packet, const Networking::NetPlayer& player)
	{
		return packet << player.id << player.name << player.color << player.ping << player.isReady << player.isWinner << player.xPosition << player.yPosition;
	}

	friend sf::Packet& operator >>(sf::Packet& packet, Networking::NetPlayer& player)
	{
		return packet >> player.id >> player.name >> player.color >> player.ping >> player.isReady >> player.isWinner >> player.xPosition >> player.yPosition;
	}
};

