#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include "Helpers.h"
#include "Vector2.h"

using namespace std;
using namespace Helpers;

class Map
{
public: 
	vector<int> map;
	int width;
	int height;
	int squareSize;

	Map();

	void draw(function<void(Vector2)> makeVertex);//int windowWidth, int windowHeight);

	bool validPosition(float xPos, float yPos);
};

