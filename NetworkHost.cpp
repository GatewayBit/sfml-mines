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
	sf::TcpListener listener;
	listener.listen(5555);
	// Create a list to store the future clients
	std::list<sf::TcpSocket*> clients;

	// Create a map to store client data.
	NetworkPlayerManager clientDataManager;

	// Create a clock to limit the amount of packets we send out.
	sf::Clock clock;

	// Create a selector
	sf::SocketSelector selector;
	// Add the listener to the selector
	selector.add(listener);

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
			if (selector.isReady(listener))
			{
				std::cout << "[SERVER] New client connection pending." << '\n';
				// The listener is ready: there is a pending connection
				sf::TcpSocket* client = new sf::TcpSocket;
				if (listener.accept(*client) == sf::Socket::Done)
				{
					std::cout << "[SERVER] Client accepted!" << '\n';
					std::cout << "[SERVER] Remote Address: " << client->getRemoteAddress() << " Remote Port: " << client->getRemotePort() << '\n';
					// Add the new client to the clients list
					clients.push_back(client);
					// Add the new client to the selector so that we will
					// be notified when he sends something
					selector.add(*client);

					// Add the clients data to a map
					// ??? Missing something here ???
					sf::Packet clientPacketData;


					client->receive(clientPacketData);
					packetsReceived++;

					Networking::NetPlayer clientData;
					clientPacketData >> clientData;

					std::cout << "**CLIENT DATA**" << '\n';
					std::cout << "ID: " << clientData.id << '\n';
					std::cout << "Name: " << clientData.name << '\n';
					std::cout << "Color: " << clientData.color << '\n';
					std::cout << "Ping: " << clientData.ping << '\n';
					std::cout << "isReady: " << clientData.isReady << '\n';
					std::cout << "isWinner: " << clientData.isWinner << '\n';
					std::cout << "xPosition: " << clientData.xPosition << '\n';
					std::cout << "yPosition: " << clientData.yPosition << '\n';

					std::cout << '\n' << "[SERVER] Saving client data." << '\n';

					clientID++;
					clientData.id = clientID;

					sf::Packet idPacket;
					idPacket << clientData;
					std::cout << "[INIT] ID: " << clientData.id << '\n';
					client->send(idPacket);

					clientDataManager.Add(client, clientData);
					std::cout << "[SERVER] Data saved." << '\n';
				}
				else
				{
					std::cout << "[SERVER] Client had problems connecting, removing." << '\n';
					// Error, we won't get a new connection, delete the socket
					delete client;
				}
			}
			else
			{
				// The listener socket is not ready, test all other sockets (the clients)
				for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++)
				{
					sf::TcpSocket* client = *it;

					if (selector.isReady(*client))
					{
						// The client has sent some data, we can receive it
						sf::Packet packet;
						if (client->receive(packet) == sf::Socket::Done)
						{
							packetsReceived++;
							Networking::NetPlayer hostData = clientDataManager.GetData(client);
							std::cout << "[SERVER] HOST DATA ID: " << hostData.id << '\n';
							Networking::NetPlayer p;

							std::cout << "[SERVER] ID: " << hostData.id << '\n';
							packet >> p;
							std::cout << "[RECEIVED] ID: " << p.id << '\n';

							if (hostData.id != p.id)
							{
								std::cout << "[SERVER] SERVER CLIENT ID MISSMATCH; CORRECTING" << '\n';
								p.id = hostData.id;
							}


							clientDataManager.SetData(client, p);





							int packetCount = 0;

							sf::Packet sendDataPacket;

							std::map<sf::TcpSocket*, Networking::NetPlayer> clientContainer = clientDataManager.GetMapObject();

							int count = 0;
							for (std::map<sf::TcpSocket*, Networking::NetPlayer>::iterator clientItr = clientContainer.begin(); clientItr != clientContainer.end(); clientItr++)
							{
								std::cout << '\n';
								std::cout << count << ") " << " Client: " << clientItr->first << " ID: " << clientItr->second.id << '\n';
								count++;
							}

							/*
							** THIS IS FOR MULTI-CLIENT PURPOSES PLEASE LEAVE IT HERE
							*/
							std::cout << "Container Size: " << clientContainer.size() << '\n';

							for (std::map<sf::TcpSocket*, Networking::NetPlayer>::iterator clientItr = clientContainer.begin(); clientItr != clientContainer.end(); clientItr++)
							{
								if (clientItr->first != client)
								{
									std::cout << "[SENDING] CLIENT: " << clientItr->first << " WITH CURRENT ID: " << clientItr->second.id << '\n';
									sendDataPacket << clientItr->second;
									client->send(sendDataPacket);
									packetsSent++;
									std::cout << "[SERVER] PACKET SENT" << '\n';
									packetCount++;
								}
							}
							std::cout << '\n' << "[SERVER] Sent " << packetCount << " packets to client: " << client << "  which has ID: " << clientDataManager.GetData(client).id << '\n';
							packetCount = 0;
						}
						else if (client->receive(packet) == sf::Socket::Disconnected)
						{
							packetsReceived++;
							std::cout << "[SERVER] CLIENT HAS DISCONNECTED." << '\n';
							clients.remove(client);
							selector.remove(*client);
							clientDataManager.Remove(client);
							break;
						}

						/*
						SEND DATA BLOCK
						*/

						/*sf::Packet sendPacket;
						Networking::NetPlayer p = clientDataManager.GetData(client);
						sendPacket << p;

						if (client->send(sendPacket) == sf::Socket::Done)
						{
							std::cout << "[SERVER] Sent data back to client." << '\n';
						}*/


					}

					/*
					IF BLOCKING ISSUE PERSISTS PLEASE TRY THIS BLOCK OF CODE HERE
					*/


					//sf::Packet sendPacket;
					//Networking::NetPlayer p = clientDataManager.GetData(client);
					//p.id = 25;
					//sendPacket << p;

					//if (client->send(sendPacket) == sf::Socket::Done)
					//{
					//	std::cout << "[SERVER] Sent data back to client." << '\n';
					//}
				}
			}
		}
		std::cout << '\n' << "Packets Sent: " << packetsSent << '\n';
		std::cout << "Packets Received: " << packetsReceived << '\n' << '\n';;

		/*
		THE FOLLOWING MESS IS INTENDED TO SEND ALL COLLECTED DATA TO ALL CLIENTS
		CONNECTED TO THE HOST. UNTIL FURTHER NOTICE PLEASE LEAVE THIS COMMENTED
		OUT SO I CAN PROPERLY DESIGN THE HOST CODE.
		*/

		//sf::Time t = clock.getElapsedTime();
		//// With 50 milliseconds we are sending 20 packets a second.
		//if (t.asMilliseconds() > sf::milliseconds(50).asMilliseconds())
		//{

		//	int currentClient = 0;
		//	int packetCount = 0;

		//	// Send all collected data to all clients!
		//	for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++)
		//	{
		//		// Current selected client
		//		sf::TcpSocket* client = *it;

		//		//std::cout << "[SERVER] Sending updates to all clients." << '\n';
		//		sf::Packet sendDataPacket;
		//		/*Networking::NetPlayer p = clientDataManager.GetData(client);*/
		//		
		//		std::map<sf::TcpSocket*, Networking::NetPlayer> clientContainer = clientDataManager.GetMapObject();

		//		/*
		//		** THIS IS FOR MULTI-CLIENT PURPOSES PLEASE LEAVE IT HERE
		//		*/
		//		std::cout << "Container Size: " << clientContainer.size() << '\n';

		//		for (std::map<sf::TcpSocket*, Networking::NetPlayer>::iterator clientItr = clientContainer.begin(); clientItr != clientContainer.end(); clientItr++)
		//		{
		//			std::cout << "Sending ID: " << clientItr->second.id << '\n';
		//			sendDataPacket << clientItr->second;
		//			client->send(sendDataPacket);
		//			std::cout << "[SERVER] PACKET SENT" << '\n';
		//			packetCount++;
		//		}
		//		currentClient++;
		//		std::cout << '\n' << "[SERVER] Sent " << packetCount << " packets to client: " << currentClient << '\n';
		//		packetCount = 0;

		//		/*sendDataPacket << p;
		//		client->send(sendDataPacket);*/

		//		//std::cout << "xPosition: " << p.xPosition << "yPosition: " << p.yPosition << '\n';
		//	}
		//	currentClient = 0;

		//	clock.restart();
		//}
	}
}