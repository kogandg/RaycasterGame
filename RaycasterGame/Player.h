#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <functional>
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
	
	float Angle;
	
	Player(Vector2 position = Vector2::Zero(), float movementSpeed = 1.5f, float rotationSpeed = 0.05f);
	//Player(int x = 0, int y = 0, float movementSpeed = 1.5f, float rotationSpeed = 0.05f);

	void Draw(int width, int height);
	void update(GLFWwindow* window, function<bool(float, float)> validatePosition);//bool (*validatePosition) (float, float));//, Map* map);
	//void update(GLFWwindow* window, Map* map);

	void displayData();

private:
	Vector2 delta;
};

