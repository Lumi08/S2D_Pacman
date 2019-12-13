#pragma once

#include "S2D/S2D.h";

#include <sstream>
#include <iostream>

using namespace S2D;

struct Button 
{
	//Stores the background image
	Texture2D* bgImg;
	//Stores the image for the buttons text
	Texture2D* textImg;
	//Stores the image for when the button is being hovered over
	Texture2D* hoveringImg;
	//Stores the hitbox for the button
	Rect* hitbox;
	//stores whether the button is being hovered over or not
	bool hovering;

	/// <summary>Button constructer.
	/// <param name="x">x pos of the button.</param>
	/// <param name="y">y pos of the button.</param>
	/// <param name="width">width of the button.</param>
	/// <param name="height">height of the button.</param>
	/// <param name="path">path for the text image of the button</param>
	/// </summary>
	Button(int x, int y, int width, int height, const char path[])
	{
		textImg = new Texture2D();
		textImg->Load(path, false);
		hoveringImg = new Texture2D();
		hoveringImg->Load("Textures/Menu/ButtonHovering.png", false);
		bgImg = new Texture2D();
		bgImg->Load("Textures/Menu/ButtonBg.png", false);
		hitbox = new Rect(x, y, width, height);
		hovering = false;
	}

	/// <summary>isHovering, checks if the mouse is hovering over the button
	/// <param name="mouseState">Stores information about the mouse.</param>
	/// <returns>true if mouse is hovering inside the buttons hitbox, else false</returns>
	/// </summary>
	bool isHovering(Input::MouseState* mouseState)
	{
		if(hitbox->Contains(Vector2(mouseState->X, mouseState->Y)))
		{
			return true;
		}
		return false;
	}

	/// <summary>isHovering, checks if the mouse is clicked by the button
	/// <param name="mouseState">Stores information about the mouse.</param>
	/// <returns>true if mouse is hovering inside the buttons hitbox and has clicked, else false</returns>
	/// </summary>
	bool isClicked(Input::MouseState* mouseState)
	{
		if (isHovering(mouseState) && mouseState->LeftButton == Input::ButtonState::PRESSED)
		{
			return true;
		}
		return false;
	}

	/// <summary>Tick, checks if hovering
	/// <param name="mouseState">Stores information about the mouse.</param>
	/// </summary>
	void tick(Input::MouseState* mouseState)
	{
		if (hitbox->Contains(Vector2(mouseState->X, mouseState->Y)))
		{
			hovering = true;
		}
		else
		{
			hovering = false;
		}
	}

	/// <summary>Draw, draws the button.</summary>
	void draw()
	{
		SpriteBatch::Draw(bgImg, hitbox, nullptr);
		SpriteBatch::Draw(textImg, hitbox, nullptr);
		if (hovering)
		{
			SpriteBatch::Draw(hoveringImg, hitbox, nullptr);
		}
	}
};

class MenuScreen
{
private:
	//Stores wether the game is in the menu screen
	bool inMenu;
	//Stores the title image
	Texture2D* titleImg;
	//Stores the background image
	Texture2D* background;
	//Stores the space the background image needs to fill
	Rect* rectangle;
	//Stores the space the title image needs to fill
	Rect* titleRect;
	//Stores data for the buttons.
	Button* playButton;
	Button* exitButton;
public:
	//Constructor and deconstructor
	MenuScreen();
	~MenuScreen();

	/// <summary>Draw function, draws the menu screen.
	/// <param name="elapsedTime">Stores the time taken between frames.</param>
	/// </summary>
	void Draw(int elapsedTime);

	/// <summary>Tick function, updates the menu screen.
	/// <param name="keyboardState">Stores info about the keyboard.</param>
	/// <param name="elapsedTime">Stores the time taken between frames.</param>
	/// </summary>
	void Tick(Input::KeyboardState* keyboardState, int elapsedTime);

	/// <summary>IsInMenu function, returns if the menu is open
	/// <returns>inMenu</returns>
	/// </summary>
	bool IsInMenu();
};

