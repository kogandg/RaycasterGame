#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "Helpers.h"

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

	void draw(int windowWidth, int windowHeight);
};

