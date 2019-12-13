#include "GameScreen.h"

GameScreen::GameScreen(int argc, char* argv[]) : Game(argc, argv)
{
	//Initialise important Game aspects
	Audio::Initialise();
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();
	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}

GameScreen::~GameScreen()
{
	delete pacman;
	
	delete pauseScreen;
	delete menuScreen;

	for (int i = 0; i < actualGhostCount; i++)
	{
		delete ghosts[i];
	}

	for (int i = 0; i < actualWallCount; i++)
	{
		delete walls[i];
	}

	for (int i = 0; i < actualMunchieCount; i++)
	{
		delete munchies[i];
	}
}

void GameScreen::LoadContent()
{
	menuScreen = new MenuScreen();
	pauseScreen = new PauseScreen();
	pacman = new Pacman();
	MapLoader* map = new MapLoader("map1.txt");
	map->LoadMapAssets(pacman, ghosts, MAXGHOSTCOUNT, walls, MAXWALLCOUNT, munchies, MAXMUNCHIECOUNT);
	map->PrintMapArray();
	actualWallCount = map->getActualWalls();
	actualGhostCount = map->getActualGhosts();
	actualMunchieCount = map->getActualMunchies();

	score = 0;
	//munchie = new Munchie(new Vector2(400.0f, 400.0f), new Rect(0.0f, 0.0f, 12, 12));
}

void GameScreen::Update(int elapsedTime)
{
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	Input::MouseState* mouseState = Input::Mouse::GetState();

	if (!pauseScreen->IsPaused() && !menuScreen->IsInMenu())
	{
		pacman->Tick(keyboardState, elapsedTime, walls, actualWallCount, ghosts, actualGhostCount);
		//munchie->Tick(elapsedTime, pacman);
		
		for (int i = 0; i < actualWallCount; i++)
		{
			walls[i]->Tick();
		}

		for (int i = 0; i < actualGhostCount; i++)
		{
			ghosts[i]->Tick(elapsedTime, walls, actualWallCount);
		}
		
		for (int i = 0; i < actualMunchieCount; i++)
		{
			munchies[i]->Tick(pacman, score);
		}


		BorderCollisions();
	}
	else
	{
		menuScreen->Tick(keyboardState, elapsedTime);
	}
	pauseScreen->Tick(keyboardState, elapsedTime);
	
}

void GameScreen::Draw(int elapsedTime)
{

	SpriteBatch::BeginDraw();
	//SpriteBatch::DrawRectangle(new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight()), Color::Black);
	std::stringstream stream;
	stream << "Score: " << score << endl;
	
	//No pausemenu due to us wanting to have the background drawn but faded. need to have logic so that the textures stop doing anim ticks
	if (!menuScreen->IsInMenu())
	{
		bool isPaused = pauseScreen->IsPaused();
		pacman->Draw(isPaused);
		//munchie->Draw(elapsedTime, isPaused);

		for (int i = 0; i < actualWallCount; i++)
		{
			walls[i]->Draw();
		}
		
		for (int i = 0; i < actualMunchieCount; i++)
		{
			munchies[i]->Draw(isPaused);
		}

		for (int i = 0; i < actualGhostCount; i++)
		{
			ghosts[i]->Draw();
		}

		SpriteBatch::DrawString(stream.str().c_str(), new Vector2(10.0f, 23.0f), Color::Green);
	}

	menuScreen->Draw(elapsedTime);
	pauseScreen->Draw(elapsedTime);

	SpriteBatch::EndDraw();
}

void GameScreen::BorderCollisions()
{
	// Right Border
	if (pacman->getX() > Graphics::GetViewportWidth())
	{
		pacman->setX(-32);
		//std::cout << "Right Border Hit" << std::endl;
	}
	//Left Border
	else if (pacman->getX() < 0 - 32)
	{
		pacman->setX(Graphics::GetViewportWidth());
		//std::cout << "Left Border Hit" << std::endl;
	}
	//Top Border
	else if (pacman->getY() < 0 - 32)
	{
		pacman->setY(Graphics::GetViewportHeight());
		//std::cout << "Top Border Hit" << std::endl;
	}
	//Bottom Border
	else if (pacman->getY() > Graphics::GetViewportHeight())
	{
		pacman->setY(-32);
		//std::cout << "Bottom Border Hit" << std::endl;
	}

	/* Logic to stop at walls.
	//Right Border
	if (_pacmanPosition->X + _pacmanSourceRect->Width > 1024)
	{
		_pacmanPosition->X = 1024 - _pacmanSourceRect->Width;
	}
	//Left Border
	else if (_pacmanPosition->X < 0)
	{
		_pacmanPosition->X = 0;
	}
	//Top Border
	else if (_pacmanPosition->Y < 0)
	{
		_pacmanPosition->Y = 0;
	}
	//Bottom Border
	else if (_pacmanPosition->Y + _pacmanSourceRect->Height > 768)
	{
		_pacmanPosition->Y = 768 - _pacmanSourceRect->Height;
	}
	*/
}