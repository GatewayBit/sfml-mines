/* 
 * File:   DebugBox.h
 * Author: cujo
 *
 * Created on March 14, 2015, 4:30 PM
 */

#ifndef DEBUGBOX_H
#define	DEBUGBOX_H
#include "SFML/Graphics.hpp"
#include <iostream>

class DebugBox : public sf::Drawable, public sf::Transformable {
public:
    DebugBox();
    virtual ~DebugBox();
    
    sf::Vector2f GetBounds() const;
    
    int GetWidth() const;
    int GetHeight() const;
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    sf::VertexArray m_vertices;
    
    int m_width;
    int m_height;
};

#endif	/* DEBUGBOX_H */

