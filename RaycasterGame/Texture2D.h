#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "Color.h"
#include "Vector2.h"

using namespace std;

const int FILE_HEADER_SIZE = 14;
const int INFORMATION_HEADER_SIZE = 40;

class Texture2D
{
public:
	vector<Color> Pixels;
	Vector2 Size;

	Texture2D(string imagePath);
	Texture2D();

	Color GetPixel(Vector2 position);
	void SetPixel(Vector2 position, Color color);

private:
	bool loadImage(string imagePath);
};

