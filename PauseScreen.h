#pragma once

#include "S2D/S2D.h"

using namespace S2D;

class PauseScreen
{
private:
	bool _paused;
	bool _pKeyDown;

	Texture2D* _background;
	Rect* _rectangle;
	Vector2* _stringPosition;

public:
	PauseScreen();
	~PauseScreen();

	void Draw(int elapsedTime);

	void Tick(Input::KeyboardState* keyBoardState, int elapsedTime);

	bool IsPaused();
};

