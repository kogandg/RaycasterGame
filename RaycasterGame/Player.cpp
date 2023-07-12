#include "Player.h"

Player::Player(int x, int y, float moveSpeed, float rotateSpeed)
{
	xPosition = x;
	yPosition = y;
	movementSpeed = moveSpeed;
	rotationSpeed = rotateSpeed;

	angle = 0;
	deltaX = cos(angle) * movementSpeed;
	deltaY = sin(angle) * movementSpeed;
}

//float length = 20;
//float lengthSpeed = 0.01;
//float calcFactor(float desiredLength, float x, float y)
//{
//	return desiredLength / (sqrt(x*x + y*y));
//}

void Player::draw(int width, int height)
{
	glPointSize(8);//need to set point size before begin
	glColor3f(1, 1, 0);

	glBegin(GL_POINTS);
	vertexInt(xPosition, yPosition, width, height);
	glEnd();

	glLineWidth(3);

	glBegin(GL_LINES);
	vertexInt(xPosition, yPosition, width, height);

	float fac = 26.6;//calcFactor(length, deltaX, deltaY);
	//cout << fac << " " << length << endl;

	vertexInt(xPosition + deltaX * fac, yPosition + deltaY * fac, width, height);
	glEnd();
}

void Player::update(GLFWwindow* window, Map* map)
{
	if (glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE && map->validPosition(xPosition + deltaX, yPosition + deltaY))
	{
		xPosition += deltaX;
		yPosition += deltaY;
	}
	if (glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE)
	{
		angle -= rotationSpeed;
		if (angle < 0)
		{
			angle += 2 * PI;
		}
		deltaX = cos(angle) * movementSpeed;
		deltaY = sin(angle) * movementSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE && map->validPosition(xPosition - deltaX, yPosition - deltaY))
	{
		xPosition -= deltaX;
		yPosition -= deltaY;
	}
	if (glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE)
	{
		angle += rotationSpeed;
		if (angle > 2 * PI)
		{
			angle -= 2 * PI;
		}
		deltaX = cos(angle) * movementSpeed;
		deltaY = sin(angle) * movementSpeed;
	}

	/*if (glfwGetKey(window, GLFW_KEY_UP) != GLFW_RELEASE)
	{
		length += lengthSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_RELEASE)
	{
		length -= lengthSpeed;
	}*/
}

void Player::displayData()
{
	cout << fixed << setprecision(5);

	cout << "Player x: " << xPosition << endl;
	cout << "Player y: " << yPosition << endl;

	cout << "Player angle: " << angle << endl;
	cout << "Player deltaX: " << deltaX << endl;
	cout << "Player deltaY: " << deltaY << endl;
}
