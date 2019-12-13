#pragma once

#include "S2D/S2D.h"

using namespace S2D;

class Wall
{
private:
	Vector2* position;
	Texture2D* texture;
	Rect* sourceRect;
	Rect* hitbox;

public:
	Wall(Vector2* pos);
	~Wall();

	void Tick();
	void Draw();
	Rect getHitbox();
	Rect* getHitboxPointer();
	//void CollisionsWithPacman(Pacman* p);
	void setTexture(const char* path);
};

