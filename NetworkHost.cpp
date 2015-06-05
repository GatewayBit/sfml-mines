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
		// Make the selector wait for data on any socket
		if (selector.wait())
		{
			// Read client input		**DONE**
			// Execute client input		**DONE**
			// Simulate/update game		**DONE**
			// For each client, send packet data about game to them **IN PROGRESS**



			// Issues
			// When running code locally, I can run the server/client just fine
			// If I run a server local and a client remote I run into both
			// wanting to receive data.

			// I think the best way to solve this is to set socket blocking to false

			// Test the socket for data
			if (selector.isReady(serverSocket))
			{
				std::cout << "[SERVER] I GOT A PACKET FROM SOMEONE." << '\n';

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
					p >> clientData;
					std::cout << "DATA HEADER: " << clientData.dataHeader << '\n';
					std::cout << "IP: " << remoteIP.toString() << '\n';
					std::cout << "PORT: " << remotePort << '\n';

					// IDLE DATA
					if (clientData.dataHeader == 0)
					{
						// Client is idle; 
						// DO NOTHING

						//clientData = clientDataManager.GetData(clientData.id);

						//p.clear();
						//p << clientData;
						//serverSocket.send(p, remoteIP, remotePort);
					}

					// INIT DATA
					if (clientData.dataHeader == 1.0)
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
						clientData.xPosition = 512;
						clientData.yPosition = 384;

						p.clear();
						p << clientData;
						serverSocket.send(p, remoteIP, remotePort);

						clientDataManager.Add(clientData.id, clientData);
					}

					// MOVE DATA
					if (clientData.dataHeader == 2.0)
					{
						// Set dataHeader to 0 to reset our data header.
						clientData.dataHeader = 0;

						float speed = 5;

						std::cout << clientData.name << " wants to move " << clientData.move << " direction." << '\n';

						if (clientData.move == "W")
						{
							clientData.yPosition -= speed;
						}
						else if (clientData.move == "A")
						{
							clientData.xPosition -= speed;
						}
						else if (clientData.move == "S")
						{
							clientData.yPosition += speed;
						}
						else if (clientData.move == "D")
						{
							clientData.xPosition += speed;
						}

						/*clientDataManager.UpdatePlayerData(clientData.id, clientData);*/

						// For each client, send packet data about game to them **IN PROGRESS**
						p.clear();
						p << clientData;
						serverSocket.send(p, remoteIP, remotePort);
					}
				}
			}
		}
		//std::cout << '\n' << "Packets Sent: " << packetsSent << '\n';
		//std::cout << "Packets Received: " << packetsReceived << '\n' << '\n';
	}
}