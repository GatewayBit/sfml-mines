#pragma once
#include "Networking.h"
#include "PlayerManager.h"

class NetworkClient
{
public:
	NetworkClient();
	~NetworkClient();

	void InitWithHost();

	void SendPacketData();
	void GetPacketData();

	void SetPlayerPacketData(Networking::NetPlayer& data);
	Networking::NetPlayer GetPlayerPacketData();

	void DisplayPacketTraffic();

private:
	sf::UdpSocket m_clientSocket;
	sf::IpAddress m_clientIP;

	Networking::NetPlayer m_playerData;

	int m_packetSent;
	int m_packetReceived;
};

