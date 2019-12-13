#include "Pacman.h"
#include <iostream>

Pacman::Pacman()
{
	texture = new Texture2D();
	texture->Load("Textures/Pacman.png", false);
	deathTexture = new Texture2D();
	deathTexture->Load("Textures/PacmanDeath.png", false);
	sourceRect = new Rect(0.0f, 0.0f, 32, 32);
	deathSourceRect = new Rect(0.0f, 0.0f, 32, 32);
	position = new Vector2(-1000, -1000);
	hitbox = new Rect(position->X, position->Y, sourceRect->Width, sourceRect->Height);

	isMoving = false;
	isAlive = true;
	speed = 0.1f;
	frameCount = 0;
	deathFrameTime = 0;
	currentDirection = STOP;
}

Pacman::~Pacman()
{
	delete texture;
	delete sourceRect;
	delete position;
}

void Pacman::MovementLogic(Input::KeyboardState* keyboardState, int elapsedTime, Wall* w[], int maxWallcount)
{
	if (keyboardState->IsKeyDown(Input::Keys::LEFTSHIFT))
	{
		speedMultiplier = 2.0f;
	}
	else
	{
		speedMultiplier = 1.0f;
	}

	totalSpeed = speed * elapsedTime * speedMultiplier; 

	if (isAlive)
	{
		//Moving right
		if (keyboardState->IsKeyDown(Input::Keys::D))
		{
			nextDirection = RIGHT;
		}
		//Moving down
		else if (keyboardState->IsKeyDown(Input::Keys::S))
		{
			nextDirection = DOWN;
		}
		//Moving left
		else if (keyboardState->IsKeyDown(Input::Keys::A))
		{
			nextDirection = LEFT;
		}
		//Moving up
		else if (keyboardState->IsKeyDown(Input::Keys::W))
		{
			nextDirection = UP;
		}
		else if (keyboardState->IsKeyDown(Input::Keys::F))
		{
			nextDirection = STOP;
		}


		switch (nextDirection)
		{
			case RIGHT:
			{
				if (currentDirection != RIGHT)
				{
					bool gap = true;

					for (int i = 0; i < maxWallcount; i++)
					{
						if (w[i]->getHitboxPointer()->Contains(Vector2(position->X + hitbox->Width + 1, position->Y + totalSpeed)) ||
							w[i]->getHitboxPointer()->Contains(Vector2(position->X + hitbox->Width + 1, position->Y + hitbox->Height - totalSpeed))) 
						{
							gap = false;
						}
					}

					if (gap)
					{
						if (currentDirection == LEFT)
						{
							position->Y = ((int)(position->Y / 32)) * 32;
						}
						else if (currentDirection == DOWN)
						{
							position->Y = ((int)(position->Y / 32 + 1)) * 32;
						}
						else if (currentDirection == UP)
						{
							position->Y = ((int)(position->Y / 32)) * 32;
						}
						currentDirection = nextDirection;
						nextDirection = STOP;
					}
				}
				break;
			}

			case DOWN:
			{
				if (currentDirection != DOWN)
				{
					bool gap = true;

					for (int i = 0; i < maxWallcount; i++)
					{
						if (w[i]->getHitboxPointer()->Contains(Vector2(position->X + totalSpeed, position->Y + hitbox->Height + 1)) ||
							w[i]->getHitboxPointer()->Contains(Vector2(position->X + hitbox->Width - totalSpeed, position->Y + hitbox->Height + 1)))
						{
							gap = false;
						}
					}

					if (gap)
					{
						if (currentDirection == UP)
						{
							position->X = ((int)(position->X / 32)) * 32;
						}
						else if (currentDirection == RIGHT)
						{
							position->X = ((int)(position->X / 32 + 1)) * 32;
						}
						else if (currentDirection == LEFT)
						{
							position->X = ((int)(position->X / 32)) * 32;
						}
						currentDirection = nextDirection;
						nextDirection = STOP;
					}
				}
				break;
			}

			case LEFT:
			{
				if (currentDirection != LEFT)
				{
					bool gap = true;

					for (int i = 0; i < maxWallcount; i++)
					{
						if (w[i]->getHitboxPointer()->Contains(Vector2(position->X - 1, position->Y + totalSpeed)) ||
							w[i]->getHitboxPointer()->Contains(Vector2(position->X - 1, position->Y + hitbox->Width - totalSpeed)))
						{
							gap = false;
						}
					}

					if (gap)
					{
						if (currentDirection == RIGHT)
						{
							position->Y = ((int)(position->Y / 32)) * 32;
						}
						else if (currentDirection == DOWN)
						{
							position->Y = ((int)(position->Y / 32 + 1)) * 32;
						}
						else if (currentDirection == UP)
						{
							position->Y = ((int)(position->Y / 32)) * 32;
						}
						currentDirection = nextDirection;
						nextDirection = STOP;
					}
				}
				break;
			}

			case UP:
			{
				if (currentDirection != UP)
				{
					bool gap = true;

					for (int i = 0; i < maxWallcount; i++)
					{
						if (w[i]->getHitboxPointer()->Contains(Vector2(position->X + totalSpeed, position->Y - 1)) ||
							w[i]->getHitboxPointer()->Contains(Vector2(position->X + hitbox->Width - totalSpeed, position->Y - 1)))
						{
							gap = false;
						}
					}

					if (gap)
					{
						if (currentDirection == DOWN)
						{
							position->X = ((int)(position->X / 32)) * 32;
						}
						else if (currentDirection == RIGHT)
						{
							position->X = ((int)(position->X / 32 + 1)) * 32;
						}
						else if (currentDirection == LEFT)
						{
							position->X = ((int)(position->X / 32)) * 32;
						}
						currentDirection = nextDirection;
						nextDirection = STOP;
					}
				}
				break;
			}
		}

		switch (currentDirection)
		{
			case RIGHT:
			{
				//Move pacman left
				position->X += totalSpeed; //Moves Pacman across X axis
				//Change the sprite to right facing pacman
				sourceRect->Y = 0;
				isMoving = true;
				break;
			}

			case DOWN:
			{
				//Move pacman down
				position->Y += totalSpeed;
				//change sprite to down
				sourceRect->Y = 32;
				isMoving = true;
				break;
			}

			case LEFT:
			{
				//Move pacman right
				position->X -= totalSpeed;
				//Change the sprite to left
				sourceRect->Y = 64;
				isMoving = true;
				break;
			}

			case UP:
			{
				//Move pacman up
				position->Y -= totalSpeed;
				//Change sprite to up
				sourceRect->Y = 96;
				isMoving = true;
				break;
			}

			default:
			{
				isMoving = false;
			}
		}
	}

}

void Pacman::CollisionsWithWall(Wall* w)
{
	if (hitbox->Intersects(w->getHitbox()))
	{
		switch (currentDirection)
		{
			case RIGHT:
			{
				position->X = w->getHitboxPointer()->X - hitbox->Width;
				//p->setAlive(false);
				break;
			}
			case UP:
			{
				position->Y = w->getHitboxPointer()->Y + hitbox->Height;
				break;
			}
			case LEFT:
			{
				position->X = w->getHitboxPointer()->X + hitbox->Width;
				break;
			}
			case DOWN:
			{
				position->Y = w->getHitboxPointer()->Y - hitbox->Height;
			}
		}
		currentDirection = STOP;
		nextDirection = STOP;
	}
}

void Pacman::CollisionsWithGhost(Ghost* g)
{
	if (hitbox->Intersects(g->getHitbox()))
	{
		if (isAlive)
		{
			cout << "Pacman was killed by " << g->getName() << endl;
			isAlive = false;
		}

	}
}

void Pacman::Tick(Input::KeyboardState* keyboardState, int elapsedTime, Wall* w[], int wallCount, Ghost* g[], int ghostCount)
{
	MovementLogic(keyboardState, elapsedTime, w, wallCount);
	for (int i = 0; i < wallCount; i++)
	{
		CollisionsWithWall(w[i]);
	}

	hitbox->X = position->X;
	hitbox->Y = position->Y;

	for (int i = 0; i < ghostCount; i++)
	{
		CollisionsWithGhost(g[i]);
	}
}

void Pacman::Draw(bool isPaused)
{
	if (isAlive)
	{
		SpriteBatch::Draw(texture, position, sourceRect);
	}
	else
	{
		SpriteBatch::Draw(deathTexture, position, deathSourceRect);

	}

	if (!isPaused)
	{
		AnimTick();
	}
}

void Pacman::AnimTick()
{
	if (!isAlive)
	{
		DeathAnimTick();
	}

	if (isMoving)
	{
		if (frameCount < 10)
		{
			sourceRect->X = 0;
			frameCount++;
		}
		else
		{
			sourceRect->X = 32;
			frameCount++;

			if (frameCount >= 20)
			{
				frameCount = 0;
			}
		}
	}
	// If he isnt moving use the resting texture
	else
	{
		sourceRect->X = 0;
	}
}

void Pacman::DeathAnimTick()
{
	if (deathFrameTime >= 5)
	{	
		if (deathSourceRect->X != 32 * 15)
		{
			deathSourceRect->X += 32;
			deathFrameTime = 0;
		}
	}
	deathFrameTime++;
}

float Pacman::getX()
{
	return position->X;
}

float Pacman::getY()
{
	return position->Y;
}

int Pacman::getWidth()
{
	return sourceRect->Width;
}

int Pacman::getHeight()
{
	return sourceRect->Height;
}

Rect Pacman::getHitbox()
{
	return Rect(hitbox->X, hitbox->Y, hitbox->Width, hitbox->Height);
}

void Pacman::setX(float x)
{
	position->X = x;
}

void Pacman::setY(float y)
{
	position->Y = y;
}

void Pacman::setAlive(bool x)
{
	isAlive = x;
}

void Pacman::setDirection(Pacman::Direction direction)
{
	this->currentDirection = direction;
}

enum Pacman::Direction Pacman::getDirection()
{
	return currentDirection;
}
