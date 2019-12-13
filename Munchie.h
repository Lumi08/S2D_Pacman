#pragma once

#include "S2D/S2D.h"
#include "Pacman.h"

using namespace S2D;

class Munchie
{
private:
	//Stores the munchies x and y position
	Vector2* position;
	//Stores the muchies texture
	Texture2D* texture;
	//Stores the location the spritebatch draws from within the texture file
	Rect* sourceRect;
	//Used for collisions with the munchie
	Rect* hitbox;
	//Sound effect for when the munchie has been eaten
	SoundEffect* pop;

	//counts how many frames have passed, used in animation
	int frameCount;
public:
	//Constructor and deconstructor
	Munchie(Vector2* pos);
	~Munchie();

	/// <summary>Tick function, updates the munchies
	/// <param name="pacman">passes into collisions with pacman.</param>
	/// <param name="score">Holds the data for the score of the game.</param>	
	/// </summary>
	void Tick(Pacman* pacman, int& score);
	/// <summary>draw function, draws the munchie
	/// <param name="isPaused">if the game is paused dont animate the munchies</param>
	/// </summary>
	void Draw(bool isPaused);
	/// <summary>collisionsWithPacman, logic for when pacman hits the munchie
	/// <param name="pacman">Data for pacman</param>
	/// <param name="score>Score for the game</param>
	/// </summary>
	void collisionWithPacman(Pacman* pacman, int& score);
	void AnimTick();
};

