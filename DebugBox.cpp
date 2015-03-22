/* 
 * File:   DebugBox.cpp
 * Author: cujo
 * 
 * Created on March 14, 2015, 4:30 PM
 */

#include "DebugBox.h"
#include "Game.h"

DebugBox::DebugBox() : m_vertices(sf::LinesStrip, 5), m_width(Game::SCREEN_WIDTH / 2), m_height(Game::SCREEN_HEIGHT / 2)
{
    m_vertices[0].position = sf::Vector2f(0, 0);
    m_vertices[1].position = sf::Vector2f(m_width, 0);
    m_vertices[2].position = sf::Vector2f(m_width, m_height);
    m_vertices[3].position = sf::Vector2f(0, m_height);
    m_vertices[4].position = sf::Vector2f(0, 0);
    
    for (int i = 0; i < m_vertices.getVertexCount(); i++)
    {
        m_vertices[i].color = sf::Color::Red;
    }
}

DebugBox::~DebugBox() 
{
}

sf::Vector2f DebugBox::GetBounds() const
{
    return sf::Vector2f(m_width, m_height);
}

int DebugBox::GetWidth() const
{
    return m_width;
}

int DebugBox::GetHeight() const
{
    return m_height;
}


void DebugBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    
    states.texture = NULL;
    
    target.draw(m_vertices, states);
}

/*
 *
 *     sf::VertexArray triangle(sf::LinesStrip, 5);
    
    triangle[0].position = sf::Vector2f(10, 10);
    triangle[1].position = sf::Vector2f(400, 10);
    triangle[2].position = sf::Vector2f(400, 250);
    triangle[3].position = sf::Vector2f(10, 250);
    triangle[4].position = sf::Vector2f(10, 10);
    
    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Red;
    triangle[2].color = sf::Color::Red;
    triangle[3].color = sf::Color::Red;
    triangle[4].color = sf::Color::Red;
 * 
 */