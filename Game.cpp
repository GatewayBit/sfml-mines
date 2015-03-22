/* 
 * File:   Game.cpp
 * Author: cujo
 * 
 * Created on March 4, 2015, 11:56 PM
 */

#include "Game.h"
#include "MineManager.h"
#include "RandomNumber.h"


// Mainly used for debug purposes at the moment.
#include <iostream>

void Game::Start()
{
    if (_gameState != Uninitialized)
        return;
    
    _mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Mines Prototype - ZiphTech");
    
    // More init code here.
    
    debugBox.setOrigin(debugBox.GetWidth() / 2, debugBox.GetHeight() / 2);
    debugBox.setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
    
    // DBG: Switch this to start directly into a certain menu in the game.
    // Default: _gameState = Game::ShowSplash;
    _gameState = Game::ShowSplash;
    
    // Our entire game loop enters here.
    while (!IsExiting())
    {
        GameLoop();
    }
    
    _mainWindow.close();
}

bool Game::IsExiting()
{
    if (_gameState == Game::Exiting)
        return true;
    else
        return false;
}

sf::RenderWindow& Game::GetWindow()
{
    return _mainWindow;
}

DebugBox& Game::GetDebugBox()
{
    return debugBox;
}

//const sf::Event& Game::GetInput()
//{
//    sf::Event e;
//    _mainWindow.pollEvent(e);
//    return e;
//}

void Game::GameLoop()
{
    sf::Event currentEvent;
    
    // START BUG NOTES
    // This is a weird temporary fix for the 
    // collision/game closing bug.
    /*
     * What happens is, when the GameLoop starts, the currentEvent
     * object immediately starts with sf::Event::Closing ONLY IF
     * the collision detection is in the loop.
     * 
     * If you were to comment out the line with the CollisionCheck
     * method you will not have this issue. I have no idea why this
     * happens but I will look into it, until then this is a temporary
     * fix.
     */
    currentEvent.type = sf::Event::GainedFocus;
    // END BUG NOTES
    
    _mainWindow.pollEvent(currentEvent);
    
    switch(_gameState)
    {
        case Game::ShowingMenu:
        {
            ShowMenu();
            InitMines(m_mineCount);
            break;
        }
        case Game::ShowSplash:
        {
            ShowSplashScreen();
            break;
        }
        case Game::Playing:
        {
            _mainWindow.clear(sf::Color(0, 0, 0));
            
            // Update here
            p.Update();
            
            
            for (m_it = _mineManager.GetMapObject().begin(); m_it != _mineManager.GetMapObject().end(); ++m_it)
            {
                m_mineCollision = p.CollisionCheck(m_it->second);
                if (m_mineCollision)
                {
                    _mineManager.Remove(m_it->first);
                }
            }
            
            m_goalCollision = p.CollisionCheck(g);
            if (m_goalCollision)
            {
                Game::_gameState = Exiting;
            }
            
            
            // Draw here
            p.Draw(_mainWindow);
            g->Draw(_mainWindow);
            _mineManager.DrawAll(_mainWindow, m_visibleMines);
            
            
            _mainWindow.draw(debugBox);
            
            _mainWindow.display();
            
            // THIS IS BUGGED IF WE DO COLLISION CHECKING
            // I HAVE NO IDEA WHY!!!!
            if (currentEvent.type == sf::Event::Closed)
            {
                _gameState = Game::Exiting;
            }
            
            if (currentEvent.type == sf::Event::KeyPressed)
            {
                if (currentEvent.key.code == sf::Keyboard::Escape)
                {
                    // This is buggy too.
                    ShowMenu();
                }
//                if (currentEvent.key.code == sf::Keyboard::F)
//                {                    
//                    if (_selectedMine == 0)
//                        m_mineItr = _mineManager.GetMapObject().begin();
//                    
//                    ++m_mineItr;
//                    
//                    if (m_mineItr != _mineManager.GetMapObject().end())
//                    {
//                        _selectedMine = m_mineItr->first;
//                    }
//                    else
//                    {
//                        m_mineItr = _mineManager.GetMapObject().begin();
//                        _selectedMine = m_mineItr->first;
//                    }
//                }
                if (currentEvent.key.code == sf::Keyboard::F5)
                {
                    m_visibleMines = !m_visibleMines;
                }
            }
            
//            if (currentEvent.type == sf::Event::MouseButtonPressed)
//            {
//                if (currentEvent.mouseButton.button == sf::Mouse::Left)
//                {
//                    //mine.SetPosition(sf::Mouse::getPosition(_mainWindow).x, sf::Mouse::getPosition(_mainWindow).y);
//                    _mineManager.Get(Game::_selectedMine)->SetPosition(sf::Mouse::getPosition(_mainWindow).x, sf::Mouse::getPosition(_mainWindow).y);
//                }
//            }
            break;
        }
    }
}

void Game::ShowSplashScreen()
{
    SplashScreen ss;
    ss.Show(_mainWindow);
    _gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
    MainMenu menu;
    MainMenu::MenuResult r = menu.Show(_mainWindow);
    switch(r)
    {
        case MainMenu::Exit:
            _gameState = Game::Exiting;
            break;
        case MainMenu::Easy:
            _gameState = Game::Playing;
            m_mineCount = 50;
            break;
        case MainMenu::Medium:
            _gameState = Game::Playing;
            m_mineCount = 150;
            break;
        case MainMenu::Hard:
            _gameState = Game::Playing;
            m_mineCount = 250;
            break;
    }
}

void Game::InitMines(int count)
{
    int x;
    int y;
    
    for (int i = 0; i < count; i++)
    {
        LandMine* mine = new LandMine();
        
        x = randNum.NewNumber(Game::debugBox.GetBounds().x / 2, Game::debugBox.GetBounds().x);
        y = randNum.NewNumber(Game::debugBox.GetBounds().y / 2, Game::debugBox.GetBounds().y);
        
        mine->SetPosition(x, y);
        
        _mineManager.Add(i, mine);
    }
}


Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
Player Game::p;
MineManager Game::_mineManager;
RandomNumber Game::randNum;
Goal* Game::g = new Goal();
DebugBox Game::debugBox;
int Game::_selectedMine = 0;
bool Game::m_visibleMines = false;
int Game::m_mineCount = 50;
bool Game::m_mineCollision = false;
bool Game::m_goalCollision = false;
std::map<int, LandMine*>::iterator Game::m_it;
std::map<int, LandMine*>::iterator Game::m_mineItr;