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

Map::Map(string fileName)
{
	squareSize = 64;
	map = vector<int>();
	textures = vector<Texture2D>();

	ifstream file;
	file.open(fileName, ios::in | ios::binary);
	if (!file.is_open())
	{
		cout << "Could not open file " << fileName << endl;
		return;
	}

	file >> width;
	file >> height;
	map.resize(width * height);

	for (int i = 0; i < map.size(); i++)
	{
		file >> map[i];
	}

	while (!file.eof())
	{
		string textureName;
		file >> textureName;

		Texture2D texture = Texture2D(textureName);
		textures.push_back(texture);
	}

	cout << "Done" << endl;
}

void Map::draw(function<void(Vector2)> makeVertex)//int windowWidth, int windowHeight)
{
	//map background : glClearColor(0.3, 0.3, 0.3, 0);
	Vector2 position;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (map[(y * width) + x] != 0)
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
			glColor3f(0.3f, 0.3f, 0.3f);
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
	Vector2 mapPos = Vector2((int)xPos / squareSize, (int)yPos / squareSize);
	return map[(mapPos.Y * width) + mapPos.X] == 0;
}
