/* 
 * File:   VisibleGameObject.h
 * Author: cujo
 *
 * Created on March 6, 2015, 6:09 PM
 */

#ifndef VISIBLEGAMEOBJECT_H
#define	VISIBLEGAMEOBJECT_H
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class VisibleGameObject
{
public:
    VisibleGameObject();
    virtual ~VisibleGameObject();
    
    virtual void Load(std::string filename);
    virtual void LoadRect(sf::Vector2f size, sf::Color c);
    
    virtual void Draw(sf::RenderWindow& window);
    virtual void Update();
    
    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual bool IsLoaded() const;
    
    virtual float GetWidth() const;
    virtual float GetHeight() const;
    
    virtual sf::Rect<float> GetBoundingBox() const;
    
    virtual std::string GetObjectType();
    
    virtual void SetObjectType(std::string type);
    
protected:
    sf::Sprite& GetSprite();
    sf::RectangleShape& GetRect();
    
    
private:
    sf::RectangleShape _rect;
    sf::Sprite _sprite;
    sf::Texture _texture;
    std::string _filename;
    std::string m_objectType;
    bool _isLoaded;
    bool _isRectangle;

};

#endif	/* VISIBLEGAMEOBJECT_H */

