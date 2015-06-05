#include "NetworkClient.h"

NetworkClient::NetworkClient() : m_packetSent(0), m_packetReceived(0), m_remotePort(5555)
{
}


NetworkClient::~NetworkClient()
{
}

void NetworkClient::InitWithHost()
{
	// INIT CLIENT NETWORK CODE
	std::cout << "[CLIENT] Running Client Init Code." << '\n';

	m_clientSocket.bind(8888);
	// THIS WILL ONLY LET CUJO DESKTOP HOST
	m_remoteIP = m_remoteIP.getPublicAddress();

	sf::Packet p;

	// SEND INIT HEADER CODE
	m_playerData.dataHeader = 1.0;

	p << m_playerData;
	m_clientSocket.send(p, m_remoteIP, m_remotePort);
	p.clear();

	sf::IpAddress remoteIP;
	unsigned short remotePort;

	if (m_clientSocket.receive(p, remoteIP, remotePort) == sf::Socket::Done)
	{
		p >> m_playerData;

		std::cout << "[CLIENT] DATA HEADER: " << m_playerData.dataHeader << '\n';
		std::cout << "[CLIENT] ID: " << m_playerData.id << '\n';
		std::cout << "[CLIENT] NAME: " << m_playerData.name << '\n';
		std::cout << "[CLIENT] PING: " << m_playerData.ping << '\n';
		std::cout << "[CLIENT] COLOR: " << m_playerData.color << '\n';
		std::cout << "[CLIENT] X: " << m_playerData.xPosition << '\n';
		std::cout << "[CLIENT] Y: " << m_playerData.yPosition << '\n';

		SetLocalPlayerPacketData(m_playerData);
	}
}

void NetworkClient::SendPacketData(Networking::NetPlayer data)
{
	sf::Packet p;
	p << data;
	m_clientSocket.send(p, m_remoteIP, m_remotePort);
}

Networking::NetPlayer NetworkClient::ReceivePacketData()
{
	sf::Packet p;
	Networking::NetPlayer data;
	m_clientSocket.receive(p, m_remoteIP, m_remotePort);

	p >> data;
	return data;
}


void NetworkClient::SetPlayerPacketData(Networking::NetPlayer& data)
{
	m_playerData = data;
}

Networking::NetPlayer NetworkClient::GetPlayerPacketData() const
{
	return m_playerData;
}

void NetworkClient::SetLocalPlayerPacketData(Networking::NetPlayer& data)
{
	m_localPlayerData = data;
}

Networking::NetPlayer NetworkClient::GetLocalPlayerPacketData() const
{
	return m_localPlayerData;
}


void NetworkClient::DisplayPacketTraffic()
{
	std::cout << '\n' << "Packet Sent: " << m_packetSent << '\n';
	std::cout << "Packet Received: " << m_packetReceived << '\n' << '\n';
}