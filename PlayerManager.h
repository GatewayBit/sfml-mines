#pragma once
#include <SFML/Graphics.hpp>
#include "VisibleGameObject.h"
#include "Player.h"


class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	void Add(int position, Player* vgo);
	void Remove(int position);
	int GetCount() const;
	Player* GetPlayerObject(int position) const;
	void UpdatePlayerData(int position, Networking::NetPlayer data);

	void DrawAll(sf::RenderWindow& window);
	void UpdateAll();
	bool CollisionCheck(VisibleGameObject* other);

	std::map<int, Player*>& GetMapObject();

private:

	std::map<int, Player*> _vgoObjects;

	struct PlayerManagerDeallocator
	{
		void operator() (const std::pair<int, Player*>& p) const
		{
			delete p.second;
		}
	};
};

