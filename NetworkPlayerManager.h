#pragma once
#include "Networking.h"

class NetworkPlayerManager
{
public:
	NetworkPlayerManager();
	~NetworkPlayerManager();

	void Add(sf::TcpSocket* client, Networking::NetPlayer clientData);
	void Remove(sf::TcpSocket* client);
	int GetCount() const;
	Networking::NetPlayer GetData(sf::TcpSocket* client) const;
	void SetData(sf::TcpSocket* client, Networking::NetPlayer clientData);

	std::map<sf::TcpSocket*, Networking::NetPlayer>& GetMapObject();

private:

	std::map<sf::TcpSocket*, Networking::NetPlayer> m_clientData;

	struct PlayerManagerDeallocator
	{
		void operator() (const std::pair<sf::TcpSocket*, Networking::NetPlayer>& p) const
		{
			delete p.first;
		}
	};
};

