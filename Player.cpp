/* 
 * File:   Player.cpp
 * Author: cujo
 * 
 * Created on March 6, 2015, 8:18 PM
 */

#include "Player.h"
#include "Game.h"

Player::Player() : _xVelocity(0.0f), _yVelocity(0.0f),
        _speed(175), _friction(0.4f), _maxVelocity(200.0f)
{
    VisibleGameObject::LoadRect(sf::Vector2f(12, 12), sf::Color(255, 0, 0));
    GetRect().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT - 125);
    VisibleGameObject::SetObjectType("player");
}

Player::~Player()
{
    
}

void Player::Update()
{
    /*
     * ===***REWORK ME***===
     * Hey, you should like totally rework this
     * mess of player control.
     * 
     * The issue is, when you push a button of movement
     * your velocity is changed by that amount and STAYS there
     * 
     * What I want it to do is when I push a button
     * move in that DIRECTION and move toward it.
     * 
     * I need to have players current position
     * and move it towards a direction by the
     * velocity not using velocity as direction.
     * 
     * Speed describes only how fast an object is moving, 
     * whereas velocity gives both how fast and in what 
     * direction the object is moving.
     */
    
    float x = GetRect().getPosition().x;
    float y = GetRect().getPosition().y;
    
    //std::cout << "X:" << x << " Y:" << y << '\n';
    
    float timeDelta = clock.restart().asSeconds();
    
    float velocity = _speed * timeDelta;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
//        _yVelocity -= _speed;
        y -= velocity;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
//        _yVelocity += _speed;
        y += velocity;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
//        _xVelocity -= _speed;
        x -= velocity;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        x += velocity;
//        _xVelocity += _speed;
        
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
    
    
    
    /*
     * This block is used to calculate friction applied
     * to the player until coming to a full stop.
     */
//    float xTemp = _xVelocity;
//    float yTemp = _yVelocity;
//
//    if (xTemp > 0)
//        _xVelocity -= _friction;
//    if (xTemp < 0)
//        _xVelocity += _friction;
//
//    if (yTemp > 0)
//        _yVelocity -= _friction;
//    if (yTemp < 0)
//        _yVelocity += _friction;
    /*
     * These are both in place to prevent the player
     * from bouncing back and forth due to the result
     * in friction reduction.
     */
//    if (_xVelocity < 0.1 && _xVelocity > -0.1)
//    {
//        _xVelocity = 0;
//    }
//    if (_yVelocity < 0.1 && _yVelocity > -0.1)
//    {
//        _yVelocity = 0;
//    }
    
    /*
     * This block is to make sure we don't exceed
     * our max velocity limit set.
     */
//    if (_xVelocity > _maxVelocity)
//        _xVelocity = _maxVelocity;
//    
//    if (_xVelocity < -_maxVelocity)
//        _xVelocity = -_maxVelocity;
//    
//    if (_yVelocity > _maxVelocity)
//        _yVelocity = _maxVelocity;
//    
//    if (_yVelocity < -_maxVelocity)
//        _yVelocity = -_maxVelocity;
    
    
//    if (xTemp > 0)
//        x -= _xVelocity;
//    if (xTemp < 0)
//        x += _xVelocity;
//
//    if (yTemp > 0)
//        y -= _yVelocity;
//    if (yTemp < 0)
//        y += _yVelocity;

    
    
//    GetRect().move(_xVelocity * timeDelta, _yVelocity * timeDelta);
    
}

void Player::Draw(sf::RenderWindow& window)
{
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