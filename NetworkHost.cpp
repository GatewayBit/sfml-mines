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
	// Create a list to store the future clients
	std::list<sf::UdpSocket*> clients;

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
			// Test the listener
			if (selector.isReady(serverSocket))
			{
				std::cout << "[SERVER] I GOT A PACKET FROM SOMEONE." << '\n';

				sf::Packet p;

				/*
				THIS IS CRUCIAL DATA FAGGOT DO NOT DELETE
				*/
				sf::IpAddress remoteIP;
				unsigned short remotePort;
				/*
				THIS IS CRUCIAL DATA FAGGOT DO NOT DELETE
				*/
				Networking::NetPlayer clientData;

				if (serverSocket.receive(p, remoteIP, remotePort) == sf::Socket::Done)
				{
					p >> clientData;
					std::cout << "DATA HEADER: " << clientData.dataHeader << '\n';
					std::cout << "IP: " << remoteIP.toString() << '\n';
					std::cout << "PORT: " << remotePort << '\n';

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
					}
				}
			}
		}
		//std::cout << '\n' << "Packets Sent: " << packetsSent << '\n';
		//std::cout << "Packets Received: " << packetsReceived << '\n' << '\n';
	}
}