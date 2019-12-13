#include "Munchie.h"
#include <iostream>
using namespace std;

Munchie::Munchie(Vector2* pos)
{
	texture = new Texture2D();
	texture->Load("Textures/Munchie.png", false);
	pop = new SoundEffect();
	pop->Load("Sounds/pop.wav");
	position = pos;
	position->X = pos->X + 10;
	position->Y = pos->Y + 10;
	sourceRect = new Rect(0, 0, 12, 12);
	frameCount = 0;
	hitbox = new Rect(position->X + 2, position->Y + 2, 8, 8);
}

Munchie::~Munchie()
{
	delete texture;
	delete sourceRect;
	delete position;
	delete pop;
}

void Munchie::Tick(Pacman* pacman, int& score)
{
	collisionWithPacman(pacman, score);
}

void Munchie::Draw(bool isPaused)
{
	//SpriteBatch::DrawRectangle(hitbox, Color::Cyan);
	SpriteBatch::Draw(texture, position, sourceRect);
	if (!isPaused)
	{
		AnimTick();
	}
}

void Munchie::collisionWithPacman(Pacman* pacman, int& score)
{
	if (hitbox->Intersects(pacman->getHitbox()))
	{
		score += 10;
		Audio::Play(pop);
		position->X = -1000;
		position->Y = -1000;
		hitbox->X = -1000;
		hitbox->Y = -1000;
	}
}

void Munchie::AnimTick()
{
	if (frameCount < 30)
	{
		sourceRect->X = 0;
		frameCount++;
	}
	else
	{
		sourceRect->X = 12;
		frameCount++;

		if (frameCount >= 60)
		{
			frameCount = 0;
		}
	}
}



