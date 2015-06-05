/* 
 * File:   Player.h
 * Author: cujo
 *
 * Created on March 6, 2015, 8:18 PM
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include "VisibleGameObject.h"
#include "RandomNumber.h"
#include "Networking.h"


#include <iostream>

class Player : public VisibleGameObject
{
public:
    Player();
    ~Player();

    void Update();
    void Draw(sf::RenderWindow& window);
    
    bool CollisionCheck(VisibleGameObject* other);

	void SetIsClient(bool client);

	Networking::NetPlayer GetClientData();
	void SetClientData(Networking::NetPlayer& c);

    void Respawn();

	void SetColor(int num);
    
    private:
        RandomNumber m_randNum;
        
        float _xVelocity;
        float _yVelocity;
        
        const float _speed;
        const float _friction;
        const float _maxVelocity;

		sf::Color _color;

		bool m_isClient;

		Networking::NetPlayer clientData;
        
        sf::Clock clock;
};

#endif	/* PLAYER_H */

