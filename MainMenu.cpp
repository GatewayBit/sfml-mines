/* 
 * File:   MainMenu.cpp
 * Author: cujo
 * 
 * Created on March 5, 2015, 12:17 AM
 */

#include <list>

#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
    sf::Texture texture;
    texture.loadFromFile("images/MainMenu.png");
    
    sf::Sprite sprite(texture);
    
    MenuItem playButton;
    //Draw play button rect coords here
    playButton.rect.top = 93;
    playButton.rect.left = 50;
    playButton.rect.width = 289;
    playButton.rect.height = 214;
    playButton.action = Easy;
    
    MenuItem medButton;
    medButton.rect.top = 93;
    medButton.rect.left = 390;
    medButton.rect.width = 629;
    medButton.rect.height = 214;
    medButton.action = Medium;
    
    MenuItem hardButton;
    hardButton.rect.top = 93;
    hardButton.rect.left = 721;
    hardButton.rect.width = 960;
    hardButton.rect.height = 214;
    hardButton.action = Hard;
    
    MenuItem exitButton;
    //Draw exit button rect coords here
    exitButton.rect.top = 487;
    exitButton.rect.left = 390;
    exitButton.rect.width = 628;
    exitButton.rect.height = 607;
    exitButton.action = Exit;
    
    _menuItems.push_back(playButton);
    _menuItems.push_back(medButton);
    _menuItems.push_back(hardButton);
    _menuItems.push_back(exitButton);
    
    window.draw(sprite);
    window.display();
    
    return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
    sf::Event e;
    
    while(true)
    {
        while(window.pollEvent(e))
        {
            if (e.type == sf::Event::MouseButtonPressed)
            {
//                PrintMouseCoord(e.mouseButton.x, e.mouseButton.y);
                return HandleClick(e.mouseButton.x, e.mouseButton.y);
            }
            if (e.type == sf::Event::Closed)
            {
                return Exit;
            }
        }
    }
}

// This is used to debug the actual positions of the buttons shown on screen.

void MainMenu::PrintMouseCoord(int x, int y)
{
    std::cout << "Mouse X: " << x << " Mouse Y: " << y << std::endl;
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
    std::list<MenuItem>::iterator itr;
    
    for (itr = _menuItems.begin(); itr != _menuItems.end(); itr++)
    {
        sf::Rect<int> menuItemRect = (*itr).rect;
        if (menuItemRect.height > y
                && menuItemRect.top < y
                && menuItemRect.left < x
                && menuItemRect.width > x)
        {
            return (*itr).action;
        }
    }
}