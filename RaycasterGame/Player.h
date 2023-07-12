#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include "Helpers.h"


using namespace Helpers;
using namespace std;

class Player
{
public: 
	float xPosition;
	float yPosition;
	float movementSpeed;
	float rotationSpeed;
	
	float deltaY;
	float deltaX;
	float angle;

	Player(int x = 0, int y = 0, float moveSpeed = 1.5f, float rotateSpeed = 0.05f);

	void draw(int width, int height);
	void update(GLFWwindow* window);

	void displayData();
};

