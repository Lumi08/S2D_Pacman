#ifndef Pacman_Included 
#define Pacman_Included

#include "S2D/S2D.h"
#include "Wall.h"
#include "Ghost.h"

#include <iostream>

using namespace S2D;

class Pacman
{
public:

	//enum to store pacmans direction
	enum Direction
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		STOP
	};

	//constructor & deconstructor
	Pacman();
	~Pacman();

	/// <summary>Tick function, used to update pacman
	/// <param name="keyboardState">stores data about the keyboard.</param>
	/// <param name="elapsedTime">time between each frame.</param>
	/// <param name="walls">Data for all the walls</param>
	/// <param name="wallCount">number of walls in array</param>
	/// <param name="ghosts">Data for all the ghosts</param>
	/// <param name="ghostCount">number of ghosts in array</param>
	void Tick(Input::KeyboardState* keyboardState, int elapsedTime, Wall* w[], int wallCount, Ghost* g[], int ghostCount);
	/// <summary>Draw function, Draws pacman in the correct positions
	/// <param name="isPaused">if the games paused dont animate pacman
	/// </summary>
	void Draw(bool isPaused);

	//Getters & setters

	float getX();
	float getY();

	int getWidth();
	int getHeight();

	Rect getHitbox();

	void setX(float x);
	void setY(float y);

	void setAlive(bool x);

	void setDirection(Pacman::Direction direction);

	Direction getDirection();

private:
	//Pacmans position, x & y
	Vector2* position;
	//stores pacmans texture
	Texture2D* texture;
	//stores pacmans death texture
	Texture2D* deathTexture;
	//Rect for drawing the correct sprite from the texture sheet
	Rect* sourceRect;
	//Rect for drawing the correct sprite from the texture sheet
	Rect* deathSourceRect;
	//Hitbox for pacman used in collisions logic
	Rect* hitbox;

	//Directions used to make sure pacman doesnt turn before getting to a wall gap.
	Direction currentDirection;
	Direction nextDirection;

	int frameCount,
		deathFrameTime;
	float speed;
	float speedMultiplier;
	float totalSpeed;
	bool isMoving,
		isAlive;
	const float _cPacmanSpeed = 0.1f;

	void MovementLogic(Input::KeyboardState* keyboardState, int elapsedTime, Wall* w[], int maxWallcount);
	void CollisionsWithWall(Wall* w);
	void CollisionsWithGhost(Ghost* g);
	void AnimTick();
	void DeathAnimTick();
};
class Wall;


#endif 