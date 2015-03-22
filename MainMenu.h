/* 
 * File:   MainMenu.h
 * Author: cujo
 *
 * Created on March 5, 2015, 12:17 AM
 */

#ifndef MAINMENU_H
#define	MAINMENU_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <list>
#include <iostream>

class MainMenu {
public:
    enum MenuResult
    {
        Nothing,
        Exit,
        Easy,
        Medium,
        Hard
    };
    
    struct MenuItem
    {
    public:
        sf::Rect<int> rect;
        MenuResult action;
    };
    
    MenuResult Show(sf::RenderWindow& window);
    
private:
    MenuResult GetMenuResponse(sf::RenderWindow& window);
    MenuResult HandleClick(int x, int y);
    
    void PrintMouseCoord(int x, int y);
    
    std::list<MenuItem> _menuItems;
};

#endif	/* MAINMENU_H */

