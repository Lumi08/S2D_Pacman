#include "S2D/S2D.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Wall.h"
#include "Munchie.h"

#include <fstream>
#include <string>
#include <iostream>

#define TILESIZE 32
#define MAPTILEDWIDTH 32
#define MAPTILEDHEIGHT 24

using namespace S2D;

#pragma once
class MapLoader
{
public:
	/// <summary>MapLoader constructer, sets up the MapLoader class.
	/// <param name="path">Path for the file to read from.
	/// </summary>
	MapLoader(const char* path);
	/// <summary>Maploader deconstructer, deletes all the relevant data in the MapLoader class.</summary>
	~MapLoader();

	/// <summary>PrintMapArray, prints the map to the console.</summary>
	void PrintMapArray();
	/// <summary>LoadMapAssets function, loads all the maps positions and textures needed for the asset.
	/// <param name="pacman">Sets pacmans position according to the map.</param>
	/// <param name="ghosts">Array to store all the ghosts and their relevant data.</param>
	/// <param name="maxGhostCount>The max num of ghosts that can be stored.</param>
	/// <param name="walls">Array to store all the walls and their relevant data.</param>
	/// <param name="maxWallCount">The max num of walls that can be stored.</param>
	/// <param name="munchies">Array to store all the munchies and their relevant data.</param>
	/// <param name="maxMunchieCount">The max num of munchies that can be stored.</param>
	/// </summary>
	void LoadMapAssets(Pacman* pacman, Ghost* ghosts[], int maxGhostCount, Wall* walls[], int maxWallCount, Munchie* munchies[], int maxMunchieCount);
	/// <summary>FixWallTexture function, sets the wall to have the correct function so it has a smoother look.
	/// <param name="wall">Wall to be checking if the texture needs to change.</param>
	/// <param name="y">the y pos the wall is in the 2d char array.</param>
	/// <param name="x">The x pos the wall is in the 2d char array.</param>
	/// </summary>
	void FixWallTexture(Wall* w, int y, int x);
	
	/// <summary>Gets the actual num of ghosts stored in the ghosts array
	/// <returns>Actual ghosts in ghosts array</returns>
	/// </summary>
	int getActualGhosts();
	/// <summary>Gets the actual num of walls stored in the walls array
	/// <returns>Actual num of walls in walls array</returns>
	/// </summary>
	int getActualWalls();
	/// <summary>Gets the actual num of munchies stored in the munchies array
	/// <returns>Actual num of munchies in munchies array</returns>
	/// </summary>
	int getActualMunchies();

private:
	//Array storing all the data for the map from the .txt
	char mapArray[24][32];

	//Counters to stop out of bounds errors
	int rowCount = 0,
		wallCount = 0,
		ghostCount = 0,
		munchieCount = 0,
		pacmanCount = 0;
	
	/// <summary>MapError function, if theres an error prints error and ends the program
	/// <param name="error">String for the error.</param>
	/// </summary>
	void MapError(string error);

};


