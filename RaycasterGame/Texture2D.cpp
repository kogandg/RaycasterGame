#include "Texture2D.h"

Texture2D::Texture2D(string imagePath)
{
    Pixels = vector<Color>();
    Size = Vector2();

	if (!loadImage(imagePath))
	{
		cout << "Could not load image into texture" << endl;
	}
}

Texture2D::Texture2D()
{
}

Color Texture2D::GetPixel(Vector2 position)
{
	return Pixels[position.Y * Size.X + position.X];
}

void Texture2D::SetPixel(Vector2 position, Color color)
{
	Pixels[position.Y * Size.X + position.X] = color;
}

bool Texture2D::loadImage(string imagePath)
{
    ifstream file;
	file.open(imagePath, ios::in | ios::binary);

	if (!file.is_open())
	{
		cout << "Could not open file " << imagePath << endl;
		return false;
	}

	unsigned char fileHeader[FILE_HEADER_SIZE];
	unsigned char informationHeader[INFORMATION_HEADER_SIZE];

	file.read(reinterpret_cast<char*>(fileHeader), FILE_HEADER_SIZE);

	if (fileHeader[0] != 'B' || fileHeader[1] != 'M')
	{
		cout << "File " << imagePath << " is not a bitmap image" << endl;
		file.close();
		return false;
	}

	file.read(reinterpret_cast<char*>(informationHeader), INFORMATION_HEADER_SIZE);
	int fileSize = readInt(fileHeader, 2);

	Size = Vector2(readInt(informationHeader, 4), readInt(informationHeader, 8));

	Pixels.resize(Size.X * Size.Y);

	const int padding = ((4 - ((int)Size.X * 3) % 4) % 4);

	for (int y = Size.Y - 1; y >= 0; y--)
	{
		for (int x = 0; x < Size.X; x++)
		{
			unsigned char color[3];
			file.read(reinterpret_cast<char*>(color), 3);
			
			Pixels[y * Size.X + x] = Color((float)(color[2]) / 255.0f, (float)(color[1]) / 255.0f, (float)(color[0]) / 255.0f);
		}
		file.ignore(padding);
	}

	file.close();
	return true;
}
