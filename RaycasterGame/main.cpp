#include <GLFW/glfw3.h>
#include <iostream>
#include <limits>

#include "Helpers.h"
#include "Player.h"
#include "Map.h"

using namespace std;
using namespace Helpers;

int windowWidth = 1024;
int windowHeight = 512;

int screenWidth = 160;
int screenHeight = 320;

Player* player;
Map* map;


void drawRays()
{
	int mapX;
	int mapY;
	int mapIndex;
	int depthOfField;

	float rayXPos;
	float rayYPos;
	float rayAngle;
	float xOffset;
	float yOffset;

	float distH;
	float horiX;
	float horiY;
	float distV;
	float vertiX;
	float vertiY;
	float finalDist;

	rayAngle = player->angle - DEG*30;
	if (rayAngle < 0)
	{
		rayAngle += 2 * PI;
	}
	if (rayAngle > 2 * PI)
	{
		rayAngle -= 2 * PI;
	}

	for (int r = 0; r < 60; r++)
	{
		//check horizontal lines
		distH = numeric_limits<float>::max();
		horiX = player->xPosition;
		horiY = player->yPosition;

		depthOfField = 0;
		float aTan = -1 / tan(rayAngle);

		if (rayAngle > PI)//ray looking up
		{
			rayYPos = (((int)player->yPosition / 64) * 64) - 0.0001;//rounding to nearest 64bit and subtract for accuracy
			rayXPos = (player->yPosition - rayYPos) * aTan + player->xPosition;
			yOffset = -64;
			xOffset = -yOffset * aTan;
		}
		if (rayAngle < PI)//ray looking down
		{
			rayYPos = (((int)player->yPosition / 64) * 64) +64;//rounding to nearest 64bit
			rayXPos = (player->yPosition - rayYPos) * aTan + player->xPosition;
			yOffset = 64;
			xOffset = -yOffset * aTan;
		}
		if (rayAngle == 0 || rayAngle == PI)//looking exactly left or right
		{
			rayXPos = player->xPosition;
			rayYPos = player->yPosition;
			depthOfField = 8;
		}

		while (depthOfField < 8)
		{
			mapX = (int)(rayXPos) / 64;
			mapY = (int)(rayYPos) / 64;
			mapIndex = mapY * map->width + mapX;

			if (mapIndex >= 0 && mapIndex < map->map.size() && map->map[mapIndex] == 1)//wall
			{
				depthOfField = 8;
				
				horiX = rayXPos;
				horiY = rayYPos;
				distH = distance(player->xPosition, player->yPosition, horiX, horiY);
			}
			else 
			{
				rayXPos += xOffset;
				rayYPos += yOffset;
				depthOfField++;
			}
		}



		//check vertical lines
		distV = numeric_limits<float>::max();
		vertiX = player->xPosition;
		vertiY = player->yPosition;

		depthOfField = 0;
		float nTan = -tan(rayAngle);

		if (rayAngle > P2 && rayAngle < P3)//ray looking left
		{
			rayXPos = (((int)player->xPosition / 64) * 64) - 0.0001;//rounding to nearest 64bit and subtract for accuracy
			rayYPos = (player->xPosition - rayXPos) * nTan + player->yPosition;
			xOffset = -64;
			yOffset = -xOffset * nTan;
		}
		if (rayAngle < P2 || rayAngle > P3)//ray looking right
		{
			rayXPos = (((int)player->xPosition / 64) * 64) + 64;//rounding to nearest 64bit
			rayYPos = (player->xPosition - rayXPos) * nTan + player->yPosition;
			xOffset = 64;
			yOffset = -xOffset * nTan;
		}
		if (rayAngle == P2 || rayAngle == P3)//looking exactly up or down
		{
			rayXPos = player->xPosition;
			rayYPos = player->yPosition;
			depthOfField = 8;
		}

		while (depthOfField < 8)
		{
			mapX = (int)(rayXPos) / 64;
			mapY = (int)(rayYPos) / 64;
			mapIndex = mapY * map->width + mapX;

			if (mapIndex >= 0 && mapIndex < map->map.size() && map->map[mapIndex] == 1)//wall
			{
				depthOfField = 8;

				vertiX = rayXPos;
				vertiY = rayYPos;
				distV = distance(player->xPosition, player->yPosition, vertiX, vertiY);
			}
			else
			{
				rayXPos += xOffset;
				rayYPos += yOffset;
				depthOfField++;
			}
		}

		glColor3f(1, 0, 0);
		//get smallest ray, either hit vertical wall or horizontal wall
		if (distV < distH)//hit vertical wall
		{
			rayXPos = vertiX;
			rayYPos = vertiY;
			finalDist = distV;
			glColor3f(0.9, 0, 0);
		}
		if (distH < distV)//hit horizontal wall
		{
			rayXPos = horiX;
			rayYPos = horiY;
			finalDist = distH;
			glColor3f(0.6, 0, 0);
		}

		//draw current ray
		
		glLineWidth(1);
		glBegin(GL_LINES);
		vertexInt(player->xPosition, player->yPosition, windowWidth, windowHeight);
		vertexInt(rayXPos, rayYPos, windowWidth, windowHeight);
		glEnd();


		//draw 3d walls
		float cosAngle = player->angle - rayAngle;
		if (cosAngle < 0)
		{
			cosAngle += 2 * PI;
		}
		if (cosAngle > 2 * PI)
		{
			cosAngle -= 2 * PI;
		}
		finalDist *= cos(cosAngle);//fixes fisheye look

		float lineHeight = (map->squareSize * screenHeight) / finalDist;
		
		if (lineHeight > 320)
		{
			lineHeight = 320;
		}
		float lineOffset = screenHeight - lineHeight / 2;

		glLineWidth(8);
		glBegin(GL_LINES);
		vertexInt(r*8 + 530, lineOffset, windowWidth, windowHeight);
		vertexInt(r * 8 + 530, lineHeight+lineOffset, windowWidth, windowHeight);
		glEnd();

		//increase angle
		rayAngle += DEG;
		if (rayAngle < 0)
		{
			rayAngle += 2 * PI;
		}
		if (rayAngle > 2 * PI)
		{
			rayAngle -= 2 * PI;
		}
	}

}


void init(GLFWwindow* window)
{
	glClearColor(0.3, 0.3, 0.3, 0);
	glfwSetWindowSize(window, windowWidth, windowHeight);

	player = new Player(300, 300, 0.75, 0.015);
	map = new Map();
}

void update(GLFWwindow* window)
{
	player->update(window, map);
}

void draw(GLFWwindow* window)
{
	glClearColor(0.3, 0.3, 0.3, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	map->draw(windowWidth, windowHeight);
	drawRays();
	player->draw(windowWidth, windowHeight);
	
	glfwSwapBuffers(window);
}

void displayUtil()//since it clears the screen every update, its impossible to read
{
	std::cout << "\x1B[2J\x1B[H";//clears the screen
	player->displayData();
}

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

