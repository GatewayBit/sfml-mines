#pragma once
#include "Networking.h"
#include "PlayerManager.h"

class NetworkClient
{
public:
	NetworkClient();
	~NetworkClient();

	void InitWithHost();

	void SendPacketData(Networking::NetPlayer data);
	Networking::NetPlayer ReceivePacketData();

	void SetPlayerPacketData(Networking::NetPlayer& data);
	Networking::NetPlayer GetPlayerPacketData() const;

	void SetLocalPlayerPacketData(Networking::NetPlayer& data);
	Networking::NetPlayer GetLocalPlayerPacketData() const;

	void SetRemoteIP(std::string ip);

	void DisplayPacketTraffic();

private:

	sf::Clock m_clock;
	sf::Time m_endTime;

	sf::UdpSocket m_clientSocket;
	sf::IpAddress m_remoteIP;
	unsigned short m_remotePort;

	Networking::NetPlayer m_playerData;
	Networking::NetPlayer m_localPlayerData;

	int m_packetSent;
	int m_packetReceived;
};

