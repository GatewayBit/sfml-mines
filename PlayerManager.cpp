#include <algorithm>
#include "PlayerManager.h"


PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
	std::for_each(_vgoObjects.begin(), _vgoObjects.end(), PlayerManagerDeallocator());
}

void PlayerManager::Add(int position, Player* vgoObject)
{
	_vgoObjects.insert(std::pair<int, Player*>(position, vgoObject));
}

void PlayerManager::Remove(int position)
{
	std::map<int, Player*>::iterator it = _vgoObjects.find(position);
	if (it != _vgoObjects.end())
	{
		delete it->second;
		_vgoObjects.erase(it);
	}
}

Player* PlayerManager::GetPlayerObject(int position) const
{
	std::map<int, Player*>::const_iterator it = _vgoObjects.find(position);
	if (it == _vgoObjects.end())
	{
		return NULL;
	}
	return it->second;
}

std::map<int, Player*>& PlayerManager::GetMapObject()
{
	return _vgoObjects;
}

int PlayerManager::GetCount() const
{
	return _vgoObjects.size();
}

void PlayerManager::DrawAll(sf::RenderWindow& window)
{
	std::map<int, Player*>::const_iterator itr = _vgoObjects.begin();

	while (itr != _vgoObjects.end())
	{
		itr->second->Draw(window);
		itr++;
	}
}

void PlayerManager::UpdateAll()
{
	std::map<int, Player*>::const_iterator itr = _vgoObjects.begin();
	
	while (itr != _vgoObjects.end())
	{
		itr->second->Update();
		itr++;
	}
}

bool PlayerManager::CollisionCheck(VisibleGameObject* other)
{
	std::map<int, Player*>::const_iterator itr = _vgoObjects.begin();
	
	while (itr != _vgoObjects.end())
	{
		if (itr->second->CollisionCheck(other))
		{
			return true;
		}
		itr++;
	}
	return false;
}

void PlayerManager::UpdatePlayerData(int position, Networking::NetPlayer data)
{
	std::map<int, Player*>::const_iterator itr = _vgoObjects.find(position);
	while (itr != _vgoObjects.end())
	{
		itr->second->SetClientData(data);
		itr++;
	}
}