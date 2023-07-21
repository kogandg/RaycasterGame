#include "Game.h"

Game::Game()
{
	player = new Player(Vector2(300, 300), 0.75, 0.015);
	map = new Map();


	mapViewPanel = new MapViewPanel(Vector2(0, 0), Vector2(150, 150), Vector2(512, 512));
	playerViewPanel = new PlayerViewPanel(Vector2(0, 0), Vector2(1024, 512), Vector2(320, 160));

	panels = { mapViewPanel, playerViewPanel };

	fov = 60;
	numRays = 200;
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
	mapViewPanel->Draw(window);
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
	//int mapX;
	//int mapY;

	Ray currentRay;
	/*float rayXPos;
	float rayYPos;*/
	float currentRayAngle;
	Vector2 offset;
	/*float xOffset;
	float yOffset;*/

	Ray horizontal;
	//float distH;
	/*float horiX;
	float horiY;*/
	Ray vertical;
	//float distV;
	/*float vertiX;
	float vertiY;*/
	//float finalDist;

	currentRayAngle = player->Angle - DEG * fov / 2;
	normalizeAngle(currentRayAngle);

	for (int r = 0; r < numRays; r++)
	{
		currentRay = Ray(player->Position);

		//check horizontal lines

		//horizontal = Ray(player->Position, Vector2::Zero());
		//distH = numeric_limits<float>::max();
		horizontal = Ray(player->Position);
		/*horiX = player->Position.X;
		horiY = player->Position.Y;*/

		depthOfField = 0;
		float nmioTan = -1 / tan(currentRayAngle);//negative multiplicative inverse of tangent

		if (currentRayAngle > PI)//ray looking up
		{
			//currentRay.RayVector.Y = (((int)player->Position.Y / 64) * 64) - 0.0001;// - player->Position.Y;
			//currentRay.RayVector.X = (player->Position.Y - currentRay.RayVector.Y) * nmioTan + player->Position.X;

			currentRay.End.Y = (((int)player->Position.Y / 64) * 64) - 0.0001;// - player->Position.Y;
			currentRay.End.X = (player->Position.Y - currentRay.End.Y) * nmioTan + player->Position.X;

			//rayYPos = (((int)player->Position.Y / 64) * 64) - 0.0001;//rounding to nearest 64bit and subtract for accuracy
			//rayXPos = (player->Position.Y - rayYPos) * nmioTan + player->Position.X;

			offset.Y = -map->squareSize;
			offset.X = -offset.Y * nmioTan;
			/*yOffset = -map->squareSize;
			xOffset = -yOffset * nmioTan;*/
		}
		if (currentRayAngle < PI)//ray looking down
		{
			//currentRay.RayVector.Y = (((int)player->Position.Y / 64) * 64) + map->squareSize;// -player->Position.Y;
			//currentRay.RayVector.X = (player->Position.Y - currentRay.RayVector.Y) * nmioTan + player->Position.X;

			currentRay.End.Y = (((int)player->Position.Y / 64) * 64) + map->squareSize;
			currentRay.End.X = (player->Position.Y - currentRay.End.Y) * nmioTan + player->Position.X;

			//rayYPos = (((int)player->Position.Y / 64) * 64) + map->squareSize;//rounding to nearest 64bit
			//rayXPos = (player->Position.Y - rayYPos) * nmioTan + player->Position.X;

			offset.Y = map->squareSize;
			offset.X = -offset.Y * nmioTan;
			/*yOffset = map->squareSize;
			xOffset = -yOffset * nmioTan;*/
		}
		if (currentRayAngle == 0 || currentRayAngle == PI)//looking exactly left or right
		{
			//currentRay.RayVector = Vector2::Zero();

			currentRay.End = player->Position;

			/*rayXPos = player->Position.X;
			rayYPos = player->Position.Y;*/
			depthOfField = 8;
		}

		while (depthOfField < 8)
		{
			/*mapPos.X = (int)(currentRay.RayEnd().X) / map->squareSize;
			mapPos.Y = (int)(currentRay.RayEnd().Y) / map->squareSize;
			mapIndex = mapPos.Y * map->width + mapPos.X;*/

			mapPos.X = (int)(currentRay.End.X) / map->squareSize;
			mapPos.Y = (int)(currentRay.End.Y) / map->squareSize;
			//mapX = (int)(rayXPos) / map->squareSize;
			//mapY = (int)(rayYPos) / map->squareSize;
			mapIndex = mapPos.Y * map->width + mapPos.X;

			if (mapIndex >= 0 && mapIndex < map->map.size() && map->map[mapIndex] == 1)//wall
			{
				depthOfField = 8;

				//horizontal = currentRay;
				//horizontal.RayVector = currentRay.RayVector;
				/*horiX = rayXPos;
				horiY = rayYPos;*/
				//distH = distance(player->Position.X, player->Position.Y, horizontal.RayVector.X, horizontal.RayVector.Y);
			}
			else
			{
				//currentRay.RayVector += offset;

				currentRay.End += offset;
				/*rayXPos += offset.X;
				rayYPos += offset.Y;*/

				/*rayXPos += xOffset;
				rayYPos += yOffset;*/
				depthOfField++;
			}
		}
		horizontal = currentRay;


		//check vertical lines
		//vertical = Ray(player->Position, Vector2::Zero());
		//distV = numeric_limits<float>::max();
		vertical = Ray(player->Position);
		/*vertiX = player->Position.X;
		vertiY = player->Position.Y;*/

		depthOfField = 0;
		float nTan = -tan(currentRayAngle);

		if (currentRayAngle > P2 && currentRayAngle < P3)//ray looking left
		{
			//currentRay.RayVector.X = (((int)player->Position.X / 64) * 64) - 0.0001;// - player->Position.X;
			//currentRay.RayVector.Y = (player->Position.X - currentRay.RayVector.X) * nTan + player->Position.Y;

			currentRay.End.X = (((int)player->Position.X / 64) * 64) - 0.0001;
			currentRay.End.Y = (player->Position.X - currentRay.End.X) * nTan + player->Position.Y;

			//rayXPos = (((int)player->Position.X / 64) * 64) - 0.0001;//rounding to nearest 64bit and subtract for accuracy
			//rayYPos = (player->Position.X - rayXPos) * nTan + player->Position.Y;

			/*offset.X = -map->squareSize;
			offset.Y = -offset.X * nTan;*/

			offset.X = -map->squareSize;
			offset.Y = -offset.X * nTan;

			/*xOffset = -map->squareSize;
			yOffset = -xOffset * nTan;*/
		}
		if (currentRayAngle < P2 || currentRayAngle > P3)//ray looking right
		{
			//currentRay.RayVector.X = (((int)player->Position.X / 64) * 64) + map->squareSize;// -player->Position.X;
			//currentRay.RayVector.Y = (player->Position.X - currentRay.RayVector.X) * nTan + player->Position.Y;

			currentRay.End.X = (((int)player->Position.X / 64) * 64) + map->squareSize;
			currentRay.End.Y = (player->Position.X - currentRay.End.X) * nTan + player->Position.Y;

			//rayXPos = (((int)player->Position.X / 64) * 64) + map->squareSize;//rounding to nearest 64bit
			//rayYPos = (player->Position.X - rayXPos) * nTan + player->Position.Y;

			/*offset.X = map->squareSize;
			offset.Y = -offset.X * nTan;*/

			offset.X = map->squareSize;
			offset.Y = -offset.X * nTan;

			/*xOffset = map->squareSize;
			yOffset = -xOffset * nTan;*/
		}
		if (currentRayAngle == P2 || currentRayAngle == P3)//looking exactly up or down
		{
			//currentRay.RayVector = Vector2::Zero();

			currentRay.End = player->Position;

			/*rayXPos = player->Position.X;
			rayYPos = player->Position.Y;*/

			depthOfField = 8;
		}

		while (depthOfField < 8)
		{
			/*mapPos.X = (int)(currentRay.RayVector.X) / map->squareSize;
			mapPos.Y = (int)(currentRay.RayVector.Y) / map->squareSize;
			mapIndex = mapPos.Y * map->width + mapPos.X;*/

			mapPos.X = (int)(currentRay.End.X) / map->squareSize;
			mapPos.Y = (int)(currentRay.End.Y) / map->squareSize;
			//mapX = (int)(rayXPos) / map->squareSize;
			//mapY = (int)(rayYPos) / map->squareSize;
			mapIndex = mapPos.Y * map->width + mapPos.X;

			if (mapIndex >= 0 && mapIndex < map->map.size() && map->map[mapIndex] == 1)//wall
			{
				depthOfField = 8;

				//vertical = currentRay;
				//vertical.RayVector = currentRay.RayVector;
				/*vertiX = rayXPos;
				vertiY = rayYPos;*/
				//distV = distance(player->Position.X, player->Position.Y, vertical.RayVector.X, vertical.RayVector.Y);
			}
			else
			{

				//currentRay.RayVector += offset;

				currentRay.End += offset;
				/*rayXPos += offset.X;
				rayYPos += offset.Y;*/

				/*rayXPos += xOffset;
				rayYPos += yOffset;*/
				depthOfField++;
			}
		}
		vertical = currentRay;

		//get smallest ray, either hit vertical wall or horizontal wall
		if (vertical.Length() < horizontal.Length())//(vertical.RayVector - vertical.Position).Length() < (horizontal.RayVector - horizontal.Position).Length())//hit vertical wall
		{
			currentRay = vertical;
			//currentRay.RayVector = vertical.RayVector;
			/*rayXPos = vertiX;
			rayYPos = vertiY;*/
			//finalDist = distV;
		}
		else//(horizontal.RayVector - horizontal.Position).Length() < (vertical.RayVector - vertical.Position).Length())//hit horizontal wall
		{
			currentRay = horizontal;
			//currentRay.RayVector = horizontal.RayVector;
			/*rayXPos = horiX;
			rayYPos = horiY;*/
			//finalDist = distH;
		}

		//Ray ray = Ray(player->Position, Vector2(rayXPos, rayYPos));
		rays[r] = currentRay;

		//increase angle
		currentRayAngle += DEG * ((float)fov / (float)numRays);
		normalizeAngle(currentRayAngle);
	}
}


