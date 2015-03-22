/* 
 * File:   MineManager.cpp
 * Author: cujo
 * 
 * Created on March 14, 2015, 10:27 AM
 */

#include <algorithm>
#include <map>

#include "MineManager.h"
#include "VisibleGameObject.h"

MineManager::MineManager() 
{
}

MineManager::~MineManager() 
{
    std::for_each(_mineObjects.begin(), _mineObjects.end(), MineObjectDeallocator());
}

void MineManager::Add(int position, LandMine* mineObject)
{
    _mineObjects.insert(std::pair<int, LandMine*>(position, mineObject));
}

void MineManager::Remove(int position)
{
    std::map<int, LandMine*>::iterator it = _mineObjects.find(position);
    if (it != _mineObjects.end())
    {
        delete it->second;
        _mineObjects.erase(it);
    }
}

LandMine* MineManager::Get(int position) const
{
    std::map<int, LandMine*>::const_iterator it = _mineObjects.find(position);
    if (it == _mineObjects.end())
    {
        return NULL;
    }
    return it->second;
}

std::map<int, LandMine*>& MineManager::GetMapObject()
{
    return _mineObjects;
}

int MineManager::GetMineCount() const
{
    return _mineObjects.size();
}

void MineManager::DrawAll(sf::RenderWindow& window, bool visible)
{
    if (visible)
    {
        std::map<int, LandMine*>::const_iterator itr = _mineObjects.begin();
        while (itr != _mineObjects.end())
        {
            itr->second->Draw(window);
            itr++;
        }
    }
}