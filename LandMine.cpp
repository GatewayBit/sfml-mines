/* 
 * File:   LandMine.cpp
 * Author: cujo
 * 
 * Created on March 10, 2015, 2:36 PM
 */

#include "LandMine.h"

LandMine::LandMine()
{
    VisibleGameObject::LoadRect(sf::Vector2f(5, 5), sf::Color(0,255,0));
    VisibleGameObject::GetRect().setPosition(50, 50);
    VisibleGameObject::SetObjectType("mine");
}

LandMine::~LandMine()
{
    
}