/* 
 * File:   Game.h
 * Author: cujo
 *
 * Created on March 4, 2015, 11:56 PM
 */

#ifndef GAME_H
#define	GAME_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "Player.h"
#include "LandMine.h"
#include "PlayerManager.h"
#include "MineManager.h"
#include "RandomNumber.h"
#include "Goal.h"
#include "DebugBox.h"
#include "Networking.h"
#include "NetworkHost.h"
#include "NetworkClient.h"


class Game {
public:
    static void Start();
    static sf::RenderWindow& GetWindow();
    //const static sf::Event& GetInput();
    static DebugBox& GetDebugBox();
    const static int SCREEN_WIDTH = 1024;
    const static int SCREEN_HEIGHT = 768;
private:
    static bool IsExiting();
    static void GameLoop();
    
    static void ShowSplashScreen();
    static void ShowMenu();
    
    static void InitMines(int count);
	static void InitPlayers(int count);
    
    enum GameState {
		Uninitialized,
		ShowSplash,
		Paused,
		ShowingMenu,
		Playing,
		Exiting,
		ClientPlayer,
		HostPlayer
    };
    
    static GameState _gameState;
    static sf::RenderWindow _mainWindow;
    //static Player p;
	static PlayerManager _playerManager;
    static MineManager _mineManager;
    static RandomNumber randNum;
    static Goal* g;
    static DebugBox debugBox;
    
    static int _selectedMine;
    static bool m_visibleMines;
    static int m_mineCount;
    static bool m_mineCollision;
    static bool m_goalCollision;

	static int m_playerCount;
    
    static std::map<int, LandMine*>::iterator m_it;
    static std::map<int, LandMine*>::iterator m_mineItr;

	static std::map<int, VisibleGameObject*>::iterator m_assetItr;
    
	static NetworkHost m_host;
};

#endif	/* GAME_H */

