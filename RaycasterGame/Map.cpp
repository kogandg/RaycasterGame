#include "Map.h"

Map::Map()
{
	map =
	{
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1
	};
	width = 8;
	height = 8;
	squareSize = 64;
}

void Map::draw(function<void(Vector2)> makeVertex)//int windowWidth, int windowHeight)
{
	//map background : glClearColor(0.3, 0.3, 0.3, 0);
	Vector2 position;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (map[(y * width) + x] == 1)
			{
				glColor3f(1, 1, 1);
			}
			else
			{
				glColor3f(0, 0, 0);
			}
			position.X = x * squareSize;
			position.Y = y * squareSize;

			glBegin(GL_QUADS);

			makeVertex(Vector2(position.X+1, position.Y+1));
			makeVertex(Vector2(position.X + 1, position.Y + squareSize - 1));
			makeVertex(Vector2(position.X + squareSize - 1, position.Y + squareSize - 1));
			makeVertex(Vector2(position.X + squareSize - 1, position.Y + 1));

			/*vertexInt(x0+1, y0+1, windowWidth, windowHeight);
			vertexInt(x0+1, y0+squareSize-1, windowWidth, windowHeight);
			vertexInt(x0 + squareSize-1, y0 + squareSize-1, windowWidth, windowHeight);
			vertexInt(x0 + squareSize-1, y0+1, windowWidth, windowHeight);*/


			glEnd();

		}
	}
}

bool Map::validPosition(float xPos, float yPos)
{
	int x0;
	int y0;
	int x1; 
	int y1;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (map[(y * width) + x] == 1)
			{
				x0 = x * squareSize;
				y0 = y * squareSize;
				x1 = x0 + squareSize;
				y1 = y0 + squareSize;

				if (x0 <= xPos && x1 >= xPos && y0 <= yPos && y1 >= yPos)
				{
					return false;
				}
			}
		}
	}
	return true;
}
