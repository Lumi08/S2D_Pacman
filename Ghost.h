#pragma once

#include "S2D/S2D.h"
#include "Wall.h"

#include <random>

using namespace S2D;

//Enum used for the direction the ghost is going
enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	STOP
};

class Ghost
{
private:
	//Stores the ghosts position
	Vector2* position;
	//Stores the ghosts texture
	Texture2D* texture;
	//Used to determine where the spritebatch should draw from the texture image
	Rect* sourceRect;
	//Used for the logic for when the ghost hits something
	Rect* hitbox;
	//The direction the ghost is going
	Direction direction;
	//Stores the name of the ghost
	string name;

	//Stores the speed of the ghost
	int speed;

	/// <summary>AnimTick function is used for the logic for animating the sprite. </summary> 
	void AnimTick();
	/// <summary>MovementLogic function updates the ghosts position depending on what direction it is going. 
	///	<param name="elapsedTime">Stores the amount of time between drawing the last fram to the current. </param>
	/// </summary>
	void MovementLogic(int elapsedTime);
	/// <summary>CollisionsWithWall function checks if the chost has hit a wall
	/// <param name="wall">The current wall that is being checked if it has been hit.
	/// </summary>
	void CollisionsWithWall(Wall* wall);

public:
	/// <summary>Ghost constructer, Used to set all the variables for the ghost and set up the objects base info.
	/// <param name="pos">The ghosts starting position</param>
	/// <param name="ghostNum">Used as a id num for the ghost.</param>
	/// </summary>
	Ghost(Vector2* pos, int ghostNum);
	/// <summary>Ghost deconstructer, deletes all the relevant data used within the ghost class.</summary>
	~Ghost();
	/// <summary>Tick function, updates all the relevant info about the ghost.
	/// <param name="elapsedTime">Stores the amount of time between drawing the last fram to the current.</param>
	/// <param name="walls">Stores data about all the walls.</param>
	/// <param name="actualWallcount">Stores the size of the walls array.</param>
	/// </summary>
	void Tick(int elapsedTime, Wall* walls[], int actualWallCount);
	/// <summary>Draw, draws the ghosts into the correct positions.</summary>
	void Draw();
	
	/// <summary>getHitbox function, gets the hitbox of the ghost.
	/// <returns>Returns the hitbox of the ghost</returns>
	/// </summary>
	Rect getHitbox();
	/// <summary>getHitbox function, gets the hitbox of the ghost.
	/// <returns>Returns the hitbox of the ghost</returns>
	/// </summary>
	string getName();
	/// <summary>getName function, gets the name of the ghost.
	/// <returns>Returns the name of the ghost</returns>
	/// </summary>
};

