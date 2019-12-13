#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

#include "S2D/S2D.h"
#include "Pacman.h"
#include "PauseScreen.h"
#include "MenuScreen.h"
#include "Munchie.h"
#include "Ghost.h"
#include "Wall.h"
#include "MapLoader.h"

#include <sstream>

//Values for map loading, stops out of range errors if a user were to add too many of each
#define MAXGHOSTCOUNT 4
#define MAXMUNCHIECOUNT 600
#define MAXWALLCOUNT 500

using namespace S2D;

class GameScreen : public Game
{
private:
	
	// Uses the pauseScreen class for all the pause screens logic.
	PauseScreen* pauseScreen;
	// Uses the menuScreen class for all the menu screen logic.
	MenuScreen* menuScreen;

	// Game objects
	Pacman* pacman;
	Munchie* munchies[MAXMUNCHIECOUNT];
	Ghost* ghosts[MAXGHOSTCOUNT];
	Wall* walls[MAXWALLCOUNT];

	// Game score
	int score;
	// actual values to avoid looping unnecessary amount of times
	int actualGhostCount;
	int actualWallCount;
	int actualMunchieCount;

	/// <summary>BorderCollisions checks if pacman has left the border of the map.</summary>
	void BorderCollisions();

public:

	/// <summary>GameScreen Constructor, starts the game and the game loop.</summary>
	GameScreen(int argc, char* argv[]);

	/// <summary>GameScreen Deconstructer, removes all assets used within the class.</summary>
	virtual ~GameScreen();

	/// <summary>LoadContent function, loads all games asset, only called once.</summary>
	void virtual LoadContent();
	
	/// <summary>Update function, Used to update all the objects positions and other data.</summary>
	void virtual Update(int elapsedTime);

	/// <summary>Draw function, Draw all the games textures after the update so they are in the correct positions.</summary>
	void virtual Draw(int elapsedTime);
};

