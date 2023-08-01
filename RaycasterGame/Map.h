#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include "Helpers.h"
#include "Vector2.h"
#include "Texture2D.h"

using namespace std;
using namespace Helpers;

class Map
{
public: 
	vector<int> map;
	int width;
	int height;
	int squareSize;

	vector<Texture2D> textures;

	Map();
	Map(string fileName);

	void draw(function<void(Vector2)> makeVertex);//int windowWidth, int windowHeight);

	bool validPosition(float xPos, float yPos);
};

