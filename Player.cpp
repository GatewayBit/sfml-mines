/* 
 * File:   Player.cpp
 * Author: cujo
 * 
 * Created on March 6, 2015, 8:18 PM
 */

#include "Player.h"
#include "Game.h"

Player::Player() : _xVelocity(0.0f), _yVelocity(0.0f),
_speed(175), _friction(0.4f), _maxVelocity(200.0f),
m_isClient(false), _color(255,0,0)
{
    VisibleGameObject::LoadRect(sf::Vector2f(12, 12), _color);
    VisibleGameObject::GetRect().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT - 125);
    VisibleGameObject::SetObjectType("player");
}

Player::~Player()
{
    
}

void Player::Update()
{
	Networking::NetPlayer netPlayer = GetClientData();

	float x;
	float y;

	x = GetRect().getPosition().x;
	y = GetRect().getPosition().y;
	
    
    float timeDelta = clock.restart().asSeconds();
    
    float velocity = _speed * timeDelta;

	netPlayer.dataHeader = 0;
	netPlayer.move = "";

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
		if (m_isClient)
		{
			netPlayer.dataHeader = 2.0;
			netPlayer.move = "W";
		}
		else
		{
			y -= velocity;
		}
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
		if (m_isClient)
		{
			netPlayer.dataHeader = 2.0;
			netPlayer.move = "S";
		}
		else
		{
			y += velocity;
		}
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
		if (m_isClient)
		{
			netPlayer.dataHeader = 2.0;
			netPlayer.move = "A";
		}
		else
		{
			x -= velocity;
		}
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
		if (m_isClient)
		{
			netPlayer.dataHeader = 2.0;
			netPlayer.move = "D";
		}
		else
		{
			x += velocity;
		}
    }
	if (m_isClient)
	{
		SetClientData(netPlayer);
	}

	GetRect().setPosition(x, y);
    
    if (x < 0)
    {
        GetRect().setPosition(0, y);
    }
    if (x > Game::SCREEN_WIDTH - GetRect().getSize().x)
    {
        GetRect().setPosition(Game::SCREEN_WIDTH - GetRect().getSize().x, y);
    }
    if (y < 0)
    {
        GetRect().setPosition(x, 0);
    }
    if (y > Game::SCREEN_HEIGHT - GetRect().getSize().y)
    {
        GetRect().setPosition(x, Game::SCREEN_HEIGHT - GetRect().getSize().y);
    }
}

void Player::Draw(sf::RenderWindow& window)
{
	if (m_isClient)
	{
		Networking::NetPlayer netPlayer = GetClientData();
		GetRect().setPosition(netPlayer.xPosition, netPlayer.yPosition);
	}
    VisibleGameObject::Draw(window);
}

bool Player::CollisionCheck(VisibleGameObject* other)
{
    bool collision = GetBoundingBox().intersects(other->GetBoundingBox());
    
    if (collision && other->GetObjectType() == "mine")
    {
        // Kill the player!
        Respawn();
        
    }
    else if (collision && other->GetObjectType() == "goal")
    {
//        Respawn();
    }
    return collision;
}

void Player::Respawn()
{
    DebugBox db = Game::GetDebugBox();
    
    bool getNumbers = true;
    bool newX = false;
    bool newY = false;
    
    int x;
    int y;
    
    x = m_randNum.NewNumber(0, Game::SCREEN_WIDTH);
    y = m_randNum.NewNumber(0, Game::SCREEN_HEIGHT);
    
    while (getNumbers)
    {
        if (newX)
            x = m_randNum.NewNumber(0, Game::SCREEN_WIDTH);
        
        if (newY)
            y = m_randNum.NewNumber(0, Game::SCREEN_HEIGHT);

//        std::cout << "Player::Respawn x: " << x << '\n';
//        std::cout << "Player::Respawn y: " << y << '\n';

        if (x > db.GetBounds().x / 2 && x < db.GetBounds().x)
        {
            // if x is greater than the left side and less than the right
            // get a new x
            newX = true;
        }
        else
        {
            newX = false;
        }
        if (y > db.GetBounds().y / 2 && y < db.GetBounds().y)
        {
            // get a new y
            newY = true;
        }
        else
        {
            newY = false;
        }
        
        if (!newX && !newY)
            getNumbers = false;
    }
    
    
    VisibleGameObject::SetPosition(x, y);
}

void Player::SetIsClient(bool client)
{
	m_isClient = client;
}

Networking::NetPlayer Player::GetClientData()
{
	return clientData;
}

void Player::SetClientData(Networking::NetPlayer& c)
{
	clientData = c;
}

void Player::SetColor(int num)
{
	sf::Color c;
	if (num == 0)
	{
		c.Red;
	}
	else if (num == 5)
	{
		c.Green;
	}
	VisibleGameObject::GetRect().setFillColor(c);
}