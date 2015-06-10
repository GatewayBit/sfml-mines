#include "NetworkHost.h"

NetworkHost::NetworkHost()
{
}


NetworkHost::~NetworkHost()
{
}

bool NetworkHost::Hosting()
{
	std::cout << "[SERVER] Init Server" << '\n';

	// Create a socket to listen to new connections
	sf::UdpSocket serverSocket;

	if (serverSocket.bind(5555) == sf::Socket::Done)
	{
		std::cout << "[SERVER] SOCKET BOUND TO PORT 5555" << '\n';
	}
	// Create a map to store client data.
	NetworkPlayerManager clientDataManager;

	// Create a selector
	sf::SocketSelector selector;
	// Add the listener to the selector
	selector.add(serverSocket);

	float clientID = 0;

	int packetsReceived = 0;
	int packetsSent = 0;

	std::cout << "[SERVER] Init complete, starting server." << '\n';
	// Endless loop that waits for new connections
	while (true)
	{
		// Read client input		**DONE**
		// Execute client input		**DONE**
		// Simulate/update game		**DONE**
		// For each client, send packet data about game to them **IN PROGRESS**

		/*
		THIS IS CRUCIAL DATA DO NOT DELETE
		*/
		sf::Packet p;
		sf::IpAddress remoteIP;
		unsigned short remotePort;
		Networking::NetPlayer clientData;
		/*
		THIS IS CRUCIAL DATA DO NOT DELETE
		*/

		// Read the data from the socket.
		if (serverSocket.receive(p, remoteIP, remotePort) == sf::Socket::Done)
		{
			m_clock.restart();

			p >> clientData;
			std::cout << "DATA HEADER: " << clientData.dataHeader << '\n';
			std::cout << "IP: " << remoteIP.toString() << '\n';
			std::cout << "PORT: " << remotePort << '\n';

			// IDLE DATA
			if (clientData.dataHeader == 0)
			{
				// Client is idle; 
				// DO NOTHING

				// **DEV NOTE**
				// I might be able to change the other header if statements
				// to else if and have this one "break". Maybe it could improve
				// performance?
			}
			// INIT DATA
			else if (clientData.dataHeader == 1.0)
			{
				clientID++;

				// Set dataHeader to 0 to reset our data header.
				clientData.dataHeader = 0;
				clientData.id = clientID;

				std::ostringstream ss;
				ss << clientID;
				std::string s_clientID(ss.str());
				std::string n = "Client " + s_clientID;
				clientData.name = n;

				clientData.ping = 0;
				clientData.color = "Red";

				clientData.moveSequenceNumber = 0;

				clientData.xPosition = 512;
				clientData.yPosition = 384;

				p.clear();
				p << clientData;
				serverSocket.send(p, remoteIP, remotePort);

				clientDataManager.Add(clientData.id, clientData);
			}

			// MOVE DATA
			else if (clientData.dataHeader == 2.0)
			{
				// Set dataHeader to 0 to reset our data header.
				clientData.dataHeader = 0;

				Networking::NetPlayer playerData = clientDataManager.GetData(clientData.id);

				if (clientData.xPosition != playerData.xPosition)
				{
					clientData.xPosition = playerData.xPosition;
				}

				if (clientData.yPosition != playerData.yPosition)
				{
					clientData.yPosition = playerData.yPosition;
				}

				float speed = 175;

				/*float velocity = speed * m_timeDelta;*/

				float velocity = 5;

				std::cout << clientData.name << " wants to move " << clientData.move << " direction." << '\n';

				if (clientData.move == "W")
				{
					clientData.yPosition -= velocity;
				}
						
				if (clientData.move == "A")
				{
					clientData.xPosition -= velocity;
				}
						
				if (clientData.move == "S")
				{
					clientData.yPosition += velocity;
				}
						
				if (clientData.move == "D")
				{
					clientData.xPosition += velocity;
				}

				clientData.serverTimeDelta = m_timeDelta;

				clientDataManager.UpdatePlayerData(clientData.id, clientData);

				//  the last acknowledged movement from the server is used as a starting point.


				// For each client, send packet data about game to them **IN PROGRESS**
				p.clear();
				p << clientData;
				serverSocket.send(p, remoteIP, remotePort);
			}
		}
		m_endTime = m_clock.getElapsedTime();
		m_timeDelta = m_endTime.asSeconds();
		std::cout << "Server Time: " << m_endTime.asMilliseconds() << '\n';
		//std::cout << '\n' << "Packets Sent: " << packetsSent << '\n';
		//std::cout << "Packets Received: " << packetsReceived << '\n' << '\n';
	}
}