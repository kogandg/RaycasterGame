#pragma once
#include <GLFW/glfw3.h>
class IPanel
{
public:
	virtual void Draw(GLFWwindow* window) = 0;
};