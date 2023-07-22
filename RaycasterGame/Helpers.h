#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

namespace Helpers
{
	void vertexInt(int x, int y, int width, int height);

	const double PI = std::atan(1.0) * 4;
	const double P2 = std::atan(1.0) * 2;
	const double P3 = std::atan(1.0) * 6;
	const double DEG = std::atan(1.0) / 45;

	float distance(float ax, float ay, float bx, float by);
	void normalizeAngle(float &angle);

	int readInt(unsigned char data[], int start);
}