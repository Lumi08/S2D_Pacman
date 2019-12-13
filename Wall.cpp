
#include "Wall.h"
#include <iostream>

using namespace S2D;

Wall::Wall(Vector2* pos)
{
	position = pos;
	texture = new Texture2D();
	texture->Load("Textures/Wall/Wall.png", false);
	sourceRect = new Rect(0.0f, 0.0f, 32, 32);

	hitbox = new Rect(position->X, position->Y, sourceRect->Width, sourceRect->Height);
}


Wall::~Wall()
{
	delete texture;
	delete position;
	delete sourceRect;
}

void Wall::Tick()
{
	
}

void Wall::Draw()
{
	SpriteBatch::Draw(texture, position, sourceRect);
}

Rect Wall::getHitbox()
{
	return Rect(hitbox->X, hitbox->Y, hitbox->Width, hitbox->Height);
}

Rect* Wall::getHitboxPointer()
{
	return hitbox;
}

void Wall::setTexture(const char* path)
{
	texture->Load(path, false);
}
