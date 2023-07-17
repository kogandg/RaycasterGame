#include <GLFW/glfw3.h>
#include <iostream>
#include <limits>

#include "Helpers.h"
#include "Player.h"
#include "Map.h"
#include "IPanel.h"
#include "MapViewPanel.h"
#include "Game.h"

using namespace std;
//using namespace Helpers;

int windowWidth = 1024;
int windowHeight = 512;

int screenWidth = 160;
int screenHeight = 320;
int screenHeightOffset = 50;

//Player* player;
//Map* map;
//MapViewPanel* mapViewPanel;

Game* game;

//void drawRays()
//{
//	int mapX;
//	int mapY;
//	int mapIndex;
//	int depthOfField;
//
//	float rayXPos;
//	float rayYPos;
//	float rayAngle;
//	float xOffset;
//	float yOffset;
//
//	float distH;
//	float horiX;
//	float horiY;
//	float distV;
//	float vertiX;
//	float vertiY;
//	float finalDist;
//
//	rayAngle = player->Angle -DEG * 30;
//	normalizeAngle(rayAngle);
//
//	for (int r = 0; r < 60; r++)
//	{
//		//check horizontal lines
//		distH = numeric_limits<float>::max();
//		horiX = player->Position.X;
//		horiY = player->Position.Y;
//
//		depthOfField = 0;
//		float aTan = -1 / tan(rayAngle);
//
//		if (rayAngle > PI)//ray looking up
//		{
//			rayYPos = (((int)player->Position.Y / 64) * 64) - 0.0001;//rounding to nearest 64bit and subtract for accuracy
//			rayXPos = (player->Position.Y - rayYPos) * aTan + player->Position.X;
//			yOffset = -64;
//			xOffset = -yOffset * aTan;
//		}
//		if (rayAngle < PI)//ray looking down
//		{
//			rayYPos = (((int)player->Position.Y / 64) * 64) + 64;//rounding to nearest 64bit
//			rayXPos = (player->Position.Y - rayYPos) * aTan + player->Position.X;
//			yOffset = 64;
//			xOffset = -yOffset * aTan;
//		}
//		if (rayAngle == 0 || rayAngle == PI)//looking exactly left or right
//		{
//			rayXPos = player->Position.X;
//			rayYPos = player->Position.Y;
//			depthOfField = 8;
//		}
//
//		while (depthOfField < 8)
//		{
//			mapX = (int)(rayXPos) / 64;
//			mapY = (int)(rayYPos) / 64;
//			mapIndex = mapY * map->width + mapX;
//
//			if (mapIndex >= 0 && mapIndex < map->map.size() && map->map[mapIndex] == 1)//wall
//			{
//				depthOfField = 8;
//
//				horiX = rayXPos;
//				horiY = rayYPos;
//				distH = distance(player->Position.X, player->Position.Y, horiX, horiY);
//			}
//			else
//			{
//				rayXPos += xOffset;
//				rayYPos += yOffset;
//				depthOfField++;
//			}
//		}
//
//
//
//		//check vertical lines
//		distV = numeric_limits<float>::max();
//		vertiX = player->Position.X;
//		vertiY = player->Position.Y;
//
//		depthOfField = 0;
//		float nTan = -tan(rayAngle);
//
//		if (rayAngle > P2 && rayAngle < P3)//ray looking left
//		{
//			rayXPos = (((int)player->Position.X / 64) * 64) - 0.0001;//rounding to nearest 64bit and subtract for accuracy
//			rayYPos = (player->Position.X - rayXPos) * nTan + player->Position.Y;
//			xOffset = -64;
//			yOffset = -xOffset * nTan;
//		}
//		if (rayAngle < P2 || rayAngle > P3)//ray looking right
//		{
//			rayXPos = (((int)player->Position.X / 64) * 64) + 64;//rounding to nearest 64bit
//			rayYPos = (player->Position.X - rayXPos) * nTan + player->Position.Y;
//			xOffset = 64;
//			yOffset = -xOffset * nTan;
//		}
//		if (rayAngle == P2 || rayAngle == P3)//looking exactly up or down
//		{
//			rayXPos = player->Position.X;
//			rayYPos = player->Position.Y;
//			depthOfField = 8;
//		}
//
//		while (depthOfField < 8)
//		{
//			mapX = (int)(rayXPos) / 64;
//			mapY = (int)(rayYPos) / 64;
//			mapIndex = mapY * map->width + mapX;
//
//			if (mapIndex >= 0 && mapIndex < map->map.size() && map->map[mapIndex] == 1)//wall
//			{
//				depthOfField = 8;
//
//				vertiX = rayXPos;
//				vertiY = rayYPos;
//				distV = distance(player->Position.X, player->Position.Y, vertiX, vertiY);
//			}
//			else
//			{
//				rayXPos += xOffset;
//				rayYPos += yOffset;
//				depthOfField++;
//			}
//		}
//
//		glColor3f(1, 0, 0);
//		//get smallest ray, either hit vertical wall or horizontal wall
//		if (distV < distH)//hit vertical wall
//		{
//			rayXPos = vertiX;
//			rayYPos = vertiY;
//			finalDist = distV;
//			glColor3f(0.9, 0, 0);
//		}
//		if (distH < distV)//hit horizontal wall
//		{
//			rayXPos = horiX;
//			rayYPos = horiY;
//			finalDist = distH;
//			glColor3f(0.6, 0, 0);
//		}
//
//		//draw current ray
//		glLineWidth(1);
//		glBegin(GL_LINES);
//		vertexInt(player->Position.X, player->Position.Y, windowWidth, windowHeight);
//		vertexInt(rayXPos, rayYPos, windowWidth, windowHeight);
//		glEnd();
//
//
//		//draw 3d walls
//		float cosAngle = player->Angle - rayAngle;
//		normalizeAngle(cosAngle);
//
//		finalDist *= cos(cosAngle);//fixes fisheye look
//
//		float lineHeight = (map->squareSize * screenHeight) / finalDist;
//
//		if (lineHeight > 320)
//		{
//			lineHeight = 320;
//		}
//		float lineOffset = ((screenHeight - lineHeight) / 2)+ screenHeightOffset;
//
//		glLineWidth(8);
//		glBegin(GL_LINES);
//		vertexInt(r * 8 + 530, lineOffset, windowWidth, windowHeight);
//		vertexInt(r * 8 + 530, lineHeight + lineOffset, windowWidth, windowHeight);
//		glEnd();
//
//		glBegin(GL_LINES);
//		glColor3f(0.2, 0.2, 0.2);
//		//vertexInt(530, screenHeight, windowWidth, windowHeight);
//		//vertexInt(530+screenWidth, screenHeight, windowWidth, windowHeight);
//
//		vertexInt(r * 8 + 530, lineHeight + lineOffset, windowWidth, windowHeight);
//		vertexInt(r * 8 + 530, screenHeight+screenHeightOffset, windowWidth, windowHeight);
//
//		glColor3f(0.4, 0.4, 0.4);
//		vertexInt(r * 8 + 530, screenHeightOffset, windowWidth, windowHeight);
//		vertexInt(r * 8 + 530, lineOffset, windowWidth, windowHeight);
//		glEnd();
//
//		//increase angle
//		rayAngle += DEG;
//		normalizeAngle(rayAngle);
//	}
//
//}



void init(GLFWwindow* window)
{
	glClearColor(0.3, 0.3, 0.3, 0);
	glfwSetWindowSize(window, windowWidth, windowHeight);

	game = new Game();
	
	/*player = new Player(300, 300, 0.75, 0.015);
	map = new Map();

	mapViewPanel = new MapViewPanel(map, player);*/
}

void update(GLFWwindow* window)
{
	game->Update(window);
	//player->update(window, [](float x, float y) -> bool {return map->validPosition(x, y); });//map);
}

void draw(GLFWwindow* window)
{
	glClearColor(0.3, 0.3, 0.3, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//map->draw(windowWidth, windowHeight);
	//player->Draw(windowWidth, windowHeight);

	game->Draw(window);

	//mapViewPanel->Draw(window);

	//drawRays();
	glfwSwapBuffers(window);
}

//void displayUtil()//since it clears the screen every update, its impossible to read
//{
//	std::cout << "\x1B[2J\x1B[H";//clears the screen
//	player->displayData();
//}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(windowWidth, windowHeight, "Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		cout << "Failed window creation";
		return -1;
	}

	init(window);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		update(window);
		draw(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

