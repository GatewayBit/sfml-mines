/* 
 * File:   MineManager.h
 * Author: cujo
 *
 * Created on March 14, 2015, 10:27 AM
 */

#ifndef MINEMANAGER_H
#define	MINEMANAGER_H
#include "LandMine.h"

class MineManager {
public:
    MineManager();
    ~MineManager();
    
    void Add(int position, LandMine* mineObject);
    void Remove(int position);
    int GetMineCount() const;
    LandMine* Get(int position) const;
    
    void DrawAll(sf::RenderWindow& window, bool visible=true);
    void UpdateAll();
    
    std::map<int, LandMine*>& GetMapObject();
    
private:
    std::map<int, LandMine*> _mineObjects;
    
    struct MineObjectDeallocator
    {
        void operator() (const std::pair<int, LandMine*>& p) const
        {
            delete p.second;
        }
    };

};

#endif	/* MINEMANAGER_H */

