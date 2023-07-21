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

			makeVertex(Vector2(position.X, position.Y));
			makeVertex(Vector2(position.X, position.Y + squareSize));
			makeVertex(Vector2(position.X + squareSize, position.Y + squareSize));
			makeVertex(Vector2(position.X + squareSize, position.Y));

			glEnd();

			glLineWidth(1);
			glColor3f(0.3, 0.3, 0.3);
			glBegin(GL_LINES);

			//top line
			makeVertex(position);
			makeVertex(Vector2(position.X+ squareSize, position.Y));

			//bottom line
			makeVertex(Vector2(position.X, position.Y + squareSize));
			makeVertex(position + squareSize);

			//left line
			makeVertex(position);
			makeVertex(Vector2(position.X, position.Y + squareSize));

			//right line
			makeVertex(Vector2(position.X + squareSize, position.Y));
			makeVertex(position + squareSize);

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
