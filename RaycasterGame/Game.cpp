#include "Game.h"

Game::Game()
{
	player = new Player(Vector2(300, 300), 0.75, 0.015);
	map = new Map();


	mapViewPanel = new MapViewPanel(Vector2(0, 0), Vector2(512, 512), Vector2(512, 512));
	playerViewPanel = new PlayerViewPanel(Vector2(0, 0), Vector2(1024, 512), Vector2(640, 320));

	panels = { mapViewPanel, playerViewPanel };

	fov = 60;
	numRays = 100;
	rays = vector<Ray>(numRays);
}

Map Game::getMap()
{
	return *map;
}

Player Game::getPlayer()
{
	return *player;
}

vector<Ray> Game::getRays()
{
	return rays;
}

void Game::Draw(GLFWwindow* window)
{
	/*for (auto panel : panels)
	{
		panel->Draw(window);
	}*/

	playerViewPanel->Draw(window);
	//mapViewPanel->Draw(window);
}

void Game::Update(GLFWwindow* window)
{
	player->update(window, [&](float x, float y) -> bool {return map->validPosition(x, y); });
	calcRays();
	mapViewPanel->GetInformation(*player, *map, rays);
	playerViewPanel->GetInformation(*player, *map, rays);
}

void Game::calcRays()
{
	Vector2 mapPos;
	int mapIndex;
	int depthOfField;

	Ray currentRay;
	float currentRayAngle;
	Vector2 offset;

	Ray horizontal;
	Ray vertical;

	currentRayAngle = player->Angle - DEG * fov / 2;
	normalizeAngle(currentRayAngle);

	for (int r = 0; r < numRays; r++)
	{
		currentRay = Ray(player->Position);

		//check horizontal lines

		horizontal = Ray(player->Position);

		depthOfField = 0;
		float nmioTan = -1 / tan(currentRayAngle);//negative multiplicative inverse of tangent

		if (currentRayAngle > PI)//ray looking up
		{
			currentRay.End.Y = (((int)player->Position.Y / 64) * 64) - 0.0001;// - player->Position.Y;
			currentRay.End.X = (player->Position.Y - currentRay.End.Y) * nmioTan + player->Position.X;

			offset.Y = -map->squareSize;
			offset.X = -offset.Y * nmioTan;
		}
		if (currentRayAngle < PI)//ray looking down
		{
			currentRay.End.Y = (((int)player->Position.Y / 64) * 64) + map->squareSize;
			currentRay.End.X = (player->Position.Y - currentRay.End.Y) * nmioTan + player->Position.X;

			offset.Y = map->squareSize;
			offset.X = -offset.Y * nmioTan;
		}
		if (currentRayAngle == 0 || currentRayAngle == PI)//looking exactly left or right
		{
			currentRay.End = player->Position;

			depthOfField = 8;
		}

		while (depthOfField < 8)
		{
			mapPos.X = (int)(currentRay.End.X) / map->squareSize;
			mapPos.Y = (int)(currentRay.End.Y) / map->squareSize;
			mapIndex = mapPos.Y * map->width + mapPos.X;

			if (mapIndex >= 0 && mapIndex < map->map.size() && map->map[mapIndex] == 1)//wall
			{
				depthOfField = 8;
				currentRay.HitVertical = false;
			}
			else
			{
				currentRay.End += offset;
				
				depthOfField++;
			}
		}
		horizontal = currentRay;


		//check vertical lines
		vertical = Ray(player->Position);

		depthOfField = 0;
		float nTan = -tan(currentRayAngle);

		if (currentRayAngle > P2 && currentRayAngle < P3)//ray looking left
		{
			currentRay.End.X = (((int)player->Position.X / 64) * 64) - 0.0001;
			currentRay.End.Y = (player->Position.X - currentRay.End.X) * nTan + player->Position.Y;

			offset.X = -map->squareSize;
			offset.Y = -offset.X * nTan;
		}
		if (currentRayAngle < P2 || currentRayAngle > P3)//ray looking right
		{
			currentRay.End.X = (((int)player->Position.X / 64) * 64) + map->squareSize;
			currentRay.End.Y = (player->Position.X - currentRay.End.X) * nTan + player->Position.Y;

			offset.X = map->squareSize;
			offset.Y = -offset.X * nTan;
		}
		if (currentRayAngle == P2 || currentRayAngle == P3)//looking exactly up or down
		{
			currentRay.End = player->Position;

			depthOfField = 8;
		}

		while (depthOfField < 8)
		{
			mapPos.X = (int)(currentRay.End.X) / map->squareSize;
			mapPos.Y = (int)(currentRay.End.Y) / map->squareSize;
			mapIndex = mapPos.Y * map->width + mapPos.X;

			if (mapIndex >= 0 && mapIndex < map->map.size() && map->map[mapIndex] == 1)//wall
			{
				depthOfField = 8;
				currentRay.HitVertical = true;
			}
			else
			{
				currentRay.End += offset;

				depthOfField++;
			}
		}
		vertical = currentRay;

		//get smallest ray, either hit vertical wall or horizontal wall
		if (vertical.Length() < horizontal.Length())//hit vertical wall
		{
			currentRay = vertical;
		}
		else//hit horizontal wall
		{
			currentRay = horizontal;
		}

		rays[r] = currentRay;

		//increase angle
		currentRayAngle += DEG * ((float)fov / (float)numRays);
		normalizeAngle(currentRayAngle);
	}
}


