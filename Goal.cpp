/* 
 * File:   Goal.cpp
 * Author: cujo
 * 
 * Created on March 14, 2015, 3:07 PM
 */

#include "Goal.h"
#include "Game.h"

Goal::Goal() 
{
    VisibleGameObject::LoadRect(sf::Vector2f(25, 25), sf::Color(255, 102, 0));
    VisibleGameObject::GetRect().setPosition(Game::SCREEN_WIDTH / 2 - 25, Game::SCREEN_HEIGHT / 2 - 25);
    VisibleGameObject::SetObjectType("goal");
}

Goal::~Goal() 
{
    
}

