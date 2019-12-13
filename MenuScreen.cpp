#include "MenuScreen.h"

MenuScreen::MenuScreen()
{
	inMenu = true;

	titleImg = new Texture2D();
	titleImg->Load("Textures/Menu/Title.png", false);
	titleRect = new Rect(258, 50, 507, 85);
	background = new Texture2D();
	background->Load("Textures/Transparency.png", false);
	rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	playButton = new Button(250, 300, 524, 100, "Textures/Menu/playButtonText.png");
	exitButton = new Button(250, 450, 524, 100, "Textures/Menu/exitButtonText.png");
}


MenuScreen::~MenuScreen()
{
	delete background;
	delete rectangle;
}

void MenuScreen::Draw(int elapsedTime)
{
	if (inMenu)
	{
		SpriteBatch::Draw(background, rectangle, nullptr);
		SpriteBatch::Draw(titleImg, titleRect, nullptr);
		playButton->draw();
		exitButton->draw();
	}
}

void MenuScreen::Tick(Input::KeyboardState* keyboardState, int elapsedTime)
{
	Input::MouseState* mouseState = Input::Mouse::GetState();

	playButton->tick(mouseState);
	exitButton->tick(mouseState);

	if (keyboardState->IsKeyDown(Input::Keys::SPACE) || playButton->isClicked(mouseState) && inMenu )
	{
		inMenu = false;
	}

	if (exitButton->isClicked(mouseState))
	{
		exit(0);
	}
}

bool MenuScreen::IsInMenu()
{
	return inMenu;
}
