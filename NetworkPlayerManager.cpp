#include "NetworkPlayerManager.h"


NetworkPlayerManager::NetworkPlayerManager()
{
}


NetworkPlayerManager::~NetworkPlayerManager()
{
	std::for_each(m_clientData.begin(), m_clientData.end(), PlayerManagerDeallocator());
}

void NetworkPlayerManager::Add(sf::TcpSocket* client, Networking::NetPlayer clientData)
{
	m_clientData.insert(std::pair<sf::TcpSocket*, Networking::NetPlayer>(client, clientData));
}

void NetworkPlayerManager::Remove(sf::TcpSocket* client)
{
	std::map<sf::TcpSocket*, Networking::NetPlayer>::iterator it = m_clientData.find(client);
	if (it != m_clientData.end())
	{
		delete it->first;
		m_clientData.erase(it);
	}
}

Networking::NetPlayer NetworkPlayerManager::GetData(sf::TcpSocket* client) const
{
	std::map<sf::TcpSocket*, Networking::NetPlayer>::const_iterator it = m_clientData.find(client);
	if (it == m_clientData.end())
	{
		/*return NULL;*/
	}
	return it->second;
}

void NetworkPlayerManager::SetData(sf::TcpSocket* client, Networking::NetPlayer clientData)
{
	std::map<sf::TcpSocket*, Networking::NetPlayer>::iterator it = m_clientData.find(client);
	if (it == m_clientData.end())
	{
		/*return NULL;*/
	}
	it->second = clientData;
}

std::map<sf::TcpSocket*, Networking::NetPlayer>& NetworkPlayerManager::GetMapObject()
{
	return m_clientData;
}

int NetworkPlayerManager::GetCount() const
{
	return m_clientData.size();
}