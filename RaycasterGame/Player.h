#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include "Helpers.h"
#include "Map.h"
#include "Vector2.h"


using namespace Helpers;
using namespace std;

class Player
{
public: 
	Vector2 Position;
	float MovementSpeed;
	float RotationSpeed;
	
	Vector2 Delta;
	float Angle;
	
	Player(Vector2 position = Vector2::Zero(), float movementSpeed = 1.5f, float rotationSpeed = 0.05f);
	Player(int x = 0, int y = 0, float movementSpeed = 1.5f, float rotationSpeed = 0.05f);

	void Draw(int width, int height);
	void update(GLFWwindow* window, Map* map);

	void displayData();
};

