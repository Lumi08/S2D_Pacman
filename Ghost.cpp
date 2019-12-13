#include "Ghost.h"
#include <iostream>
using namespace S2D;


Ghost::Ghost(Vector2* pos, int ghostNum)
{
	this->name = name;
	position = pos;
	speed = 3.0f;
	sourceRect = new Rect(0.0f, 0.0f, 32, 32);
	texture = new Texture2D();
	switch (ghostNum)
	{
		case 0:
		{
			texture->Load("Textures/Ghost/BlinkySheet.png", false);
			name = "Blinky";
			direction = UP;
			break;
		}
		case 1:
		{
			texture->Load("Textures/Ghost/InkySheet.png", false);
			name = "Inky";
			direction = LEFT;
			break;
		}
		case 2:
		{
			texture->Load("Textures/Ghost/ClydeSheet.png", false);
			name = "clyde";
			direction = RIGHT;
			break;
		}
		case 3:
		{
			texture->Load("Textures/Ghost/PinkySheet.png", false);
			name = "Pinky";
			direction = UP;
			break;
		}
	}
	hitbox = new Rect(position->X, position->Y, sourceRect->Width, sourceRect->Height);;
}


Ghost::~Ghost()
{
	delete texture;
	delete position;
	delete sourceRect;
}

void Ghost::Tick(int elapsedTime, Wall* w[], int wallCount)
{
	MovementLogic(elapsedTime);
	hitbox->X = position->X;
	hitbox->Y = position->Y;
	for (int i = 0; i < wallCount; i++)
	{
		CollisionsWithWall(w[i]);
	}
}

void Ghost::Draw()
{
	SpriteBatch::Draw(texture, position, sourceRect);
	AnimTick();
}

void Ghost::AnimTick()
{

}

void Ghost::MovementLogic(int elapsedTime)
{

	float totalSpeed = speed ;
	switch (direction)
	{
		case RIGHT:
		{
			position->X += totalSpeed;
			sourceRect->Y = 0;
			break;
		}

		case DOWN:
		{
			position->Y += totalSpeed;
			sourceRect->Y = 32;
			break;
		}

		case LEFT:
		{
			position->X -= totalSpeed;
			sourceRect->Y = 64;
			break;
		}

		case UP:
		{
			//Move pacman up
			position->Y -= totalSpeed;
			//Change sprite to up
			sourceRect->Y = 96;

			break;
		}
	}
}

void Ghost::CollisionsWithWall(Wall* w)
{
	if (hitbox->Intersects(w->getHitbox()))
	{
		switch (direction)
		{
			case RIGHT:
			{
				position->X = w->getHitboxPointer()->X - hitbox->Width;
				direction = LEFT;
				break;
			}
			case UP:
			{
				position->Y = w->getHitboxPointer()->Y + hitbox->Height;
				direction = DOWN;
				break;
			}
			case LEFT:
			{
				position->X = w->getHitboxPointer()->X + hitbox->Width;
				direction = RIGHT;
				break;
			}
			case DOWN:
			{
				position->Y = w->getHitboxPointer()->Y - hitbox->Height;
				direction = UP;
				break;
			}
		}
	}
}

Rect Ghost::getHitbox()
{
	return Rect(hitbox->X, hitbox->Y, hitbox->Width, hitbox->Height);
}

string Ghost::getName()
{
	return name;
}

