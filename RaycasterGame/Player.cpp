#include "Player.h"

Player::Player(int x, int y, float speed)
{
	xPosition = x;
	yPosition = y;
	movementSpeed = speed;
}

void Player::draw(int width, int height)
{
	glPointSize(8);//need to set point size before begin
	glColor3f(1, 1, 0);

	glBegin(GL_POINTS);
	vertexInt(xPosition, yPosition, width, height);
	glEnd();
}

void Player::update(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE)
	{
		yPosition -= movementSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE)
	{
		xPosition -= movementSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE)
	{
		yPosition += movementSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE)
	{
		xPosition += movementSpeed;
	}
}
