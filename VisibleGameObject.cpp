/* 
 * File:   VisibleGameObject.cpp
 * Author: cujo
 * 
 * Created on March 6, 2015, 6:09 PM
 */

#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject() : _isLoaded(false), _isRectangle(false)
{
    
}

VisibleGameObject::~VisibleGameObject()
{
    
}

void VisibleGameObject::Load(std::string filename)
{    
    if (!_texture.loadFromFile(filename))
    {
        _filename = "";
        _isLoaded = false;
    }
    else
    {
        _filename = filename;
        _sprite.setTexture(_texture);
        _isLoaded = true;
    }
}

void VisibleGameObject::LoadRect(sf::Vector2f size, const sf::Color c)
{
    _rect.setSize(size);
    _rect.setFillColor(c);
    _isRectangle = true;
}

void VisibleGameObject::Draw(sf::RenderWindow& window)
{
    if(_isLoaded)
        window.draw(_sprite);
    
    if(!_isLoaded && _isRectangle)
        window.draw(_rect);
}

void VisibleGameObject::Update(float elapsedTime)
{
    // Do nothing here since we will allow the inherited
    // object use this if they want.
}

void VisibleGameObject::SetPosition(float x, float y)
{
    if(_isLoaded)
        _sprite.setPosition(x, y);
    
    if(!_isLoaded && _isRectangle)
        _rect.setPosition(x, y);
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
    if(_isLoaded)
    {
        return _sprite.getPosition();
    }
    return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::GetSprite()
{
    return _sprite;
}

sf::RectangleShape& VisibleGameObject::GetRect()
{
    return _rect;
}

bool VisibleGameObject::IsLoaded() const
{
    return _isLoaded;
}

float VisibleGameObject::GetHeight() const
{
    return _sprite.getLocalBounds().height;
}

float VisibleGameObject::GetWidth() const
{
    return _sprite.getLocalBounds().width;
}

sf::Rect<float> VisibleGameObject::GetBoundingBox() const
{
    if(_isLoaded)
        return _sprite.getGlobalBounds();
    else if (!_isLoaded && _isRectangle)
        return _rect.getGlobalBounds();
}

std::string VisibleGameObject::GetObjectType()
{
    return m_objectType;
}

void VisibleGameObject::SetObjectType(std::string type)
{
    m_objectType = type;
}