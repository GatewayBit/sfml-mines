#pragma once
#include "Networking.h"
#include "PlayerManager.h"

class NetworkClient
{
public:
	NetworkClient();
	~NetworkClient();

	Networking::NetPlayer player;

	bool ConnectToHost(Networking::NetPlayer clientData);

	void SendPacketData();
	void GetPacketData();

	void SetPlayerData(Networking::NetPlayer data);
	Networking::NetPlayer GetPlayerData();

	void SetPlayerManager(PlayerManager& manager);
	PlayerManager GetPlayerManager();

	void SetPlayerPacketData(Networking::NetPlayer& data);
	Networking::NetPlayer GetPlayerPacketData();

	bool IsNewClient();
	void SetIsNewClient(bool b);

	void DisplayPacketTraffic();

private:
	sf::TcpSocket clientSocket;

	Networking::NetPlayer m_playerData;
	PlayerManager m_PlayerManager;

	int m_packetSent;
	int m_packetReceived;

	Networking::NetPlayer m_PlayerPacketData;

	bool m_newClient;
};

