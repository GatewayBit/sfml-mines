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

	// the client adds a sequence number to each request
	// when the server replies, it includes the sequence number of the last input it processed

	// the server says “based on what I’ve seen up to your request #1, your position is x = 11”.
	// Now let’s assume the client keeps a copy of the requests it sends to the server. 
	// Based on the new game state, it knows the server has already processed request #1, so it can discard that copy.
	// But it also knows the server still has to send back the result of processing request #2.
	
	// So applying client-side prediction again, the client can calculate the “present” state of the game based on the 
	// last authoritative state sent by the server, plus the inputs the server hasn’t processed yet.

	// the client gets “x = 11, last processed request = #1”. It discards its copies of sent input up to #1
	// but it retains a copy of #2, which hasn’t been acknowledged by the server.

	// It updates it internal game state with what the server sent, x = 11, and then applies all the input
	// still not seen by the server – in this case, input #2, “move to the right”

	// The end result is x = 12, which is correct.

	// a new game state arrives from the server; this time it says “x = 12, last processed request = #2”.
	// At this point, the client discards all input up to #2, and updates the state with x = 12.
	// There’s no unprocessed input to replay, so processing ends there, with the correct result.


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
		if (m_isClient)
		{
			netPlayer.dataHeader = 2.0;
			netPlayer.move = "W";

			// each user command (and the exact time it was generated) is stored on the client. The prediction algorithm uses these stored commands.
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