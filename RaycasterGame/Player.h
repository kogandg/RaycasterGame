#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include "Helpers.h"

using namespace Helpers;


class Player
{
public: 
	float xPosition;
	float yPosition;
	float movementSpeed;

	Player(int x = 0, int y = 0, float speed = 2);

	void draw(int width, int height);
	void update(GLFWwindow* window);
};

