#pragma once
#include <GLFW/glfw3.h>
#include "Vector2.h"
#include <functional>
class IPanel
{
public:
	IPanel(Vector2 position, Vector2 size, Vector2 internalSize);

	virtual void Draw(GLFWwindow* window) = 0;
	Vector2 Position;
	Vector2 Size;

protected:
	Vector2 internalSize;

	std::function<void(Vector2)> getMakeVertex();

	void makeVertex(float x, float y);
	void makeVertex(Vector2 position);
};