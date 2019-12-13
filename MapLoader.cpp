#include "MapLoader.h"


MapLoader::MapLoader(const char* path)
{
	string currentLine;
	ifstream map(path);

	if (map.is_open())
	{
		while (getline(map, currentLine))
		{
			rowCount++;
			if (rowCount > 24)
			{
				MapError("No more than 24 lines in a map file");
			}

			if (currentLine.length() != 32)
			{
				MapError("Each Line must be 32 charaters long");
			}

			for (int i = 0; i < currentLine.length(); i++)
			{
				mapArray[rowCount -1][i] = currentLine[i];
			}
		}

	}
	else
	{
		MapError("Map Not Found");
	}
}

MapLoader::~MapLoader()
{

}

void MapLoader::PrintMapArray()
{
	for (int i = 0; i < MAPTILEDHEIGHT; i++)
	{
		for (int j = 0; j < MAPTILEDWIDTH; j++)
		{
			cout << mapArray[i][j];
		}
		cout << endl;
	}
}

void MapLoader::LoadMapAssets(Pacman* p, Ghost* g[], int maxGhostCount, Wall* w[], int maxWallCount, Munchie* m[], int maxMunchieCount)
{
	for (int i = 0; i < MAPTILEDHEIGHT; i++)
	{
		for (int j = 0; j < MAPTILEDWIDTH; j++)
		{
			if (mapArray[i][j] == 'P')
			{
				pacmanCount++;

				p->setX(TILESIZE * j);
				p->setY(TILESIZE * i);
			
			}
			else if (mapArray[i][j] == 'G')
			{
				ghostCount++;
				if (ghostCount > maxGhostCount)
				{
					MapError("Too Many Ghosts in Map File");
				}

				g[ghostCount - 1] = new Ghost(new Vector2(TILESIZE * j, TILESIZE * i), ghostCount-1);
			}
			else if (mapArray[i][j] == '#')
			{
				wallCount++;
				if (wallCount > maxWallCount)
				{
					MapError("Too Many Walls in Map File");
				}

				w[wallCount - 1] = new Wall(new Vector2(TILESIZE * j, TILESIZE * i));
				FixWallTexture(w[wallCount - 1], i, j);
			}
			else if (mapArray[i][j] == '-')
			{
				munchieCount++;
				if (munchieCount > maxMunchieCount)
				{
					MapError("Too Many Munchies in Map File");
				}

				m[munchieCount - 1] = new Munchie(new Vector2(TILESIZE * j, TILESIZE * i));
			}
			/*else if (currentLine[i] == 'G')
			{
				ghostCount++;
				if (ghostCount > MAXGHOSTCOUNT)
				{
					MapError("Too Many Ghosts");
				}

				ghosts[ghostCount - 1] = new Ghost(new Vector2(32 * i, 32 * rowCount), "Textures/Ghost/InkySheet.png", "Inky");
			}*/
		}
	}


	if (pacmanCount != 1)
	{
		MapError("Pacman has not been added to the mapfile, or he has multiple spawn points!");
	}
}

void MapLoader::FixWallTexture(Wall* w, int i, int j)
{
	bool wallAbove = false,
		wallBelow = false,
		wallLeft = false,
		wallRight = false;

	if (mapArray[i - 1][j] == '#')
	{
		wallAbove = true;
	}

	if (mapArray[i + 1][j] == '#')
	{
		wallBelow = true;
	}

	if (j != 0)
	{
		if (mapArray[i][j - 1] == '#')
		{
			wallLeft = true;
		}
	}

	if (j != MAPTILEDWIDTH-1)
	{
		if (mapArray[i][j + 1] == '#')
		{
			wallRight = true;
		}
	}

	/*cout << "*******************" << endl;
	cout << "Wall: " << wallCount - 1 << endl;
	cout << "WA: " << wallAbove << endl;
	cout << "WB: " << wallBelow << endl;
	cout << "WR: " << wallRight << endl;
	cout << "WL: " << wallLeft << endl;
	cout << "*******************" << endl;*/

	if (wallAbove && wallBelow && wallRight && wallLeft)
	{
		w->setTexture("Textures/Wall/WallCross.png");
	}

	else if (wallAbove && !wallBelow && wallRight && wallLeft)
	{
		w->setTexture("Textures/Wall/WallDownT.png");
	}
	else if (wallAbove && wallBelow && wallRight && !wallLeft)
	{
		w->setTexture("Textures/Wall/WallLeftT.png");
	}
	else if (!wallAbove && wallBelow && wallRight && wallLeft)
	{
		w->setTexture("Textures/Wall/WallUpT.png");
	}
	else if (wallAbove && wallBelow && !wallRight && wallLeft)
	{
		w->setTexture("Textures/Wall/WallRightT.png");
	}
	
	else if (wallAbove && !wallBelow && wallRight && !wallLeft)
	{
		w->setTexture("Textures/Wall/WallDownToRight.png");
	}
	else if (wallAbove && !wallBelow && !wallRight && wallLeft)
	{
		w->setTexture("Textures/Wall/WallDownToLeft.png");
	}
	else if (wallAbove && wallBelow && !wallRight && !wallLeft)
	{
		w->setTexture("Textures/Wall/WallVertical.png");
	}
	else if (!wallAbove && wallBelow && wallRight && !wallLeft)
	{
		w->setTexture("Textures/Wall/WallUpToRight.png");
	}
	else if (!wallAbove && wallBelow && !wallRight && wallLeft)
	{
		w->setTexture("Textures/Wall/WallUpToLeft.png");
	}
	else if (!wallAbove && !wallBelow && wallRight && wallLeft)
	{
		w->setTexture("Textures/Wall/WallHorizontal.png");
	}
	
	else if (wallAbove && !wallBelow && !wallRight && !wallLeft)
	{
		w->setTexture("Textures/Wall/WallDown.png");
	}
	else if (!wallAbove && !wallBelow && wallRight && !wallLeft)
	{
		w->setTexture("Textures/Wall/WallLeft.png");
	}
	else if (!wallAbove && wallBelow && !wallRight && !wallLeft)
	{
		w->setTexture("Textures/Wall/WallUp.png");
	}
	else if (!wallAbove && !wallBelow && !wallRight && wallLeft)
	{
		w->setTexture("Textures/Wall/WallRight.png");
	}

	else if (!wallAbove && !wallBelow && !wallRight && !wallLeft)
	{
		w->setTexture("Textures/Wall/Wall.png");
	}
}

void MapLoader::MapError(string error)
{
	std::cout << "Map Loading Error - " << error << std::endl;
	std::cout << "Exiting..." << std::endl;
	exit(0);
}

int MapLoader::getActualGhosts()
{
	return ghostCount;
}

int MapLoader::getActualWalls()
{
	return wallCount;
}

int MapLoader::getActualMunchies()
{
	return munchieCount;
}
