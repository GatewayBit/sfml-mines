#include "NetworkClient.h"

NetworkClient::NetworkClient() : m_packetSent(0), m_packetReceived(0)
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
	m_clientIP = m_clientIP.getPublicAddress();

	sf::Packet p;
	m_playerData.dataHeader = 1.0;

	p << m_playerData;
	m_clientSocket.send(p, m_clientIP, 5555);
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
	}
}

void NetworkClient::SendPacketData()
{
	Networking::NetPlayer clientData;

	sf::Packet data;
	data << clientData;
	//if (clientSocket.send(data) == sf::Socket::Done)
	//{
	//	m_packetSent++;
	//}
	//else if (clientSocket.send(data) == sf::Socket::Disconnected)
	//{
	//	std::cout << "[CLIENT] NO CONNECTION TO HOST" << '\n';
	//	// THIS WILL DETECT IF THE CLIENT IS NOT CONNECTED TO THE HOST
	//	// BUT IT WILL NEED ADDITIONAL WORK TO MAKE THIS FUNCTION PROPERLY
	//}
}

void NetworkClient::GetPacketData()
{
	Networking::NetPlayer p;

	sf::Packet data;

	//if (clientSocket.receive(data) == sf::Socket::Done)
	//{
	//	m_packetReceived++;
	//	data >> p;
	//}
}


void NetworkClient::SetPlayerPacketData(Networking::NetPlayer& data)
{
	m_playerData = data;
}

Networking::NetPlayer NetworkClient::GetPlayerPacketData()
{
	return m_playerData;
}

void NetworkClient::DisplayPacketTraffic()
{
	std::cout << '\n' << "Packet Sent: " << m_packetSent << '\n';
	std::cout << "Packet Received: " << m_packetReceived << '\n' << '\n';
}