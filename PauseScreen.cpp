#include "PauseScreen.h"

#include <sstream>;

PauseScreen::PauseScreen()
{
	_paused = false;
	_pKeyDown = false;

	_background = new Texture2D();
	_background->Load("Textures/Transparency.png", false);
	_rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_stringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);
}

PauseScreen::~PauseScreen()
{
	delete _background;
	delete _rectangle;
	delete _stringPosition;
}

void PauseScreen::Draw(int elapsedTime)
{
	if (_paused)
	{
		std::stringstream stream;
		stream << "Paused!";

		SpriteBatch::Draw(_background, _rectangle, nullptr);
		SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Red);
	}
}

void PauseScreen::Tick(Input::KeyboardState* keyboardState, int elapsedTime)
{
	/*if (_stringPosition->X > 600)
	{
		_stringPosition->X--;
	}
	else
	{
		_stringPosition->X++;
	}*/

	if (keyboardState->IsKeyDown(Input::Keys::P) && !_pKeyDown)
	{
		_pKeyDown = true;
		_paused = !_paused;
	}

	if (keyboardState->IsKeyUp(Input::Keys::P))
	{
		_pKeyDown = false;
	}
}

bool PauseScreen::IsPaused()
{
	return _paused;
}