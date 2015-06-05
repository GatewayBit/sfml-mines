#pragma once
#include "Networking.h"

class NetworkPlayerManager
{
public:
	NetworkPlayerManager();
	~NetworkPlayerManager();

	void Add(float id, Networking::NetPlayer clientData);
	void Remove(float id);
	int GetCount() const;
	Networking::NetPlayer GetData(float id) const;
	void SetData(float id, Networking::NetPlayer clientData);

	std::map<float, Networking::NetPlayer>& GetMapObject();

private:

	std::map<float, Networking::NetPlayer> m_clientData;

	struct PlayerManagerDeallocator
	{
		void operator() (const std::pair<float, Networking::NetPlayer>& p) const
		{
			// Not using pointers.
		}
	};
};

