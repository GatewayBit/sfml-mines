#include "NetworkPlayerManager.h"


NetworkPlayerManager::NetworkPlayerManager()
{
}


NetworkPlayerManager::~NetworkPlayerManager()
{
	std::for_each(m_clientData.begin(), m_clientData.end(), PlayerManagerDeallocator());
}

void NetworkPlayerManager::Add(float id, Networking::NetPlayer clientData)
{
	m_clientData.insert(std::pair<float, Networking::NetPlayer>(id, clientData));
}

void NetworkPlayerManager::Remove(float id)
{
	std::map<float, Networking::NetPlayer>::iterator it = m_clientData.find(id);
	if (it != m_clientData.end())
	{
		m_clientData.erase(it);
	}
}

Networking::NetPlayer NetworkPlayerManager::GetData(float id) const
{
	std::map<float, Networking::NetPlayer>::const_iterator it = m_clientData.find(id);
	if (it == m_clientData.end())
	{
		/*return NULL;*/
	}
	return it->second;
}

void NetworkPlayerManager::SetData(float id, Networking::NetPlayer clientData)
{
	std::map<float, Networking::NetPlayer>::iterator it = m_clientData.find(id);
	if (it == m_clientData.end())
	{
		/*return NULL;*/
	}
	it->second = clientData;
}

std::map<float, Networking::NetPlayer>& NetworkPlayerManager::GetMapObject()
{
	return m_clientData;
}

int NetworkPlayerManager::GetCount() const
{
	return m_clientData.size();
}