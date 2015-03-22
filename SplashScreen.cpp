/* 
 * File:   SplashScreen.cpp
 * Author: cujo
 * 
 * Created on March 5, 2015, 12:10 AM
 */

#include "SplashScreen.h"
#include <iostream>

void SplashScreen::Show(sf::RenderWindow& window)
{
    sf::Texture texture;
    if (texture.loadFromFile("SplashArt.png") != true)
    {
        std::cerr << "Issues loading 'SplashArt.png'!" << std::endl;
        return;
    }
    
    sf::Sprite sprite(texture);
    
    window.draw(sprite);
    window.display();
    
    sf::Event e;
    
    // Show our Splash Screen until the user presses any key
    // or clicks any mouse button of if the game is closing.
    while(true)
    {
        while(window.pollEvent(e))
        {
            if (e.type == sf::Event::KeyPressed
                    || e.type == sf::Event::MouseButtonPressed
                    || e.type == sf::Event::Closed)
            {
                return;
            }
        }
    }
}
