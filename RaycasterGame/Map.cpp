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

void Map::draw(int windowWidth, int windowHeight)
{
	int x0;
	int y0;
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
			x0 = x * squareSize;
			y0 = y * squareSize;

			glBegin(GL_QUADS);

			vertexInt(x0+1, y0+1, windowWidth, windowHeight);
			vertexInt(x0+1, y0+squareSize-1, windowWidth, windowHeight);
			vertexInt(x0 + squareSize-1, y0 + squareSize-1, windowWidth, windowHeight);
			vertexInt(x0 + squareSize-1, y0+1, windowWidth, windowHeight);


			glEnd();

		}
	}
}
