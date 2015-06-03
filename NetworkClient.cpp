#include "NetworkClient.h"

NetworkClient::NetworkClient() : m_packetSent(0), m_packetReceived(0), m_newClient(false)
{
}


NetworkClient::~NetworkClient()
{
}

bool NetworkClient::ConnectToHost(Networking::NetPlayer clientData)
{
	// INIT CLIENT NETWORK CODE
	std::cout << "[CLIENT] Running Client Init Code." << '\n';


	sf::Socket::Status status = clientSocket.connect("64.246.108.134", 5555);
	if (status != sf::Socket::Done)
	{
		// error...
		std::cout << "[CLIENT] Something bad happened while connecting to host." << '\n';
		return false;
	}
	return true;
}

void NetworkClient::SendPacketData()
{
	Networking::NetPlayer clientData;
	sf::Clock c;
	sf::Time elapsed;

	while (true)
	{
		elapsed = c.getElapsedTime();

		// With 50 milliseconds we are sending 20 packets a second.
		if (elapsed.asMilliseconds() > sf::milliseconds(50).asMilliseconds())
		{
			sf::Packet data;
			clientData = GetPlayerData();
			data << clientData;
			if (clientSocket.send(data) == sf::Socket::Done)
			{
				m_packetSent++;
			}
			else if (clientSocket.send(data) == sf::Socket::Disconnected)
			{
				std::cout << "[CLIENT] NO CONNECTION TO HOST" << '\n';
				// THIS WILL DETECT IF THE CLIENT IS NOT CONNECTED TO THE HOST
				// BUT IT WILL NEED ADDITIONAL WORK TO MAKE THIS FUNCTION PROPERLY
			}
			c.restart();
		}
	}
}

void NetworkClient::GetPacketData()
{
	Networking::NetPlayer clientData;

	bool needID = true;
	sf::Clock c;

	while (true)
	{
		sf::Time elapsed = c.getElapsedTime();
		Networking::NetPlayer p;
		sf::Packet data;
		clientData = GetPlayerData();

		// With 50 milliseconds we are sending 20 packets a second.
		if (elapsed.asMilliseconds() > sf::milliseconds(50).asMilliseconds())
		{
			if (clientSocket.receive(data) == sf::Socket::Done)
			{
				m_packetReceived++;
				data >> p;
				
				// Received data from other client.
				if (p.id != clientData.id && !needID)
				{
					// Check if the player exists in the player manager container
					if (m_PlayerManager.GetPlayerObject(p.id) == NULL)
					{
						m_newClient = true;
						SetPlayerPacketData(p);
					}
					else
					{
						// Received data from other client
						// Grab information from container and
						// set the packet data equal to the player data.
						m_PlayerManager.GetPlayerObject(p.id)->SetClientData(p);
						std::cout << "[CLIENT] X: " << p.xPosition << " Y: " << p.yPosition << '\n';
					}
				}
				else
				{
					// Received my own data.
					// This is check upon first server response. In which case we do need an ID set.
					if (needID)
					{
						clientData.id = p.id;
						needID = false;
					}
				}
			}
			c.restart();
		}
	}
}

void NetworkClient::SetPlayerData(Networking::NetPlayer data)
{
	m_playerData = data;
}

Networking::NetPlayer NetworkClient::GetPlayerData()
{
	return m_playerData;
}

void NetworkClient::DisplayPacketTraffic()
{
	std::cout << '\n' << "Packet Sent: " << m_packetSent << '\n';
	std::cout << "Packet Received: " << m_packetReceived << '\n' << '\n';
}

void NetworkClient::SetPlayerManager(PlayerManager& manager)
{
	m_PlayerManager = manager;
}

PlayerManager NetworkClient::GetPlayerManager()
{
	return m_PlayerManager;
}

bool NetworkClient::IsNewClient()
{
	return m_newClient;
}

void NetworkClient::SetPlayerPacketData(Networking::NetPlayer& data)
{
	m_PlayerPacketData = data;
}

Networking::NetPlayer NetworkClient::GetPlayerPacketData()
{
	return m_PlayerPacketData;
}

void NetworkClient::SetIsNewClient(bool b)
{
	m_newClient = b;
}