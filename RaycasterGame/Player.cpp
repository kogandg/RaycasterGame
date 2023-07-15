#include "Player.h"

Player::Player(Vector2 position, float movementSpeed, float rotationSpeed)
{
	Position = Vector2(position);
	MovementSpeed = movementSpeed;
	RotationSpeed = rotationSpeed;

	Angle = 0;
	Delta = Vector2(cos(Angle) * movementSpeed, sin(Angle) * movementSpeed);
}

Player::Player(int x, int y, float movementSpeed, float rotationSpeed) : Player(Vector2(x, y), movementSpeed, rotationSpeed) { }

//float length = 20;
//float lengthSpeed = 0.01;
//float calcFactor(float desiredLength, float x, float y)
//{
//	return desiredLength / (sqrt(x*x + y*y));
//}

void Player::Draw(int width, int height)
{
	glPointSize(8);//need to set point size before begin
	glColor3f(1, 1, 0);

	glBegin(GL_POINTS);
	vertexInt(Position.X, Position.Y, width, height);
	glEnd();

	glLineWidth(3);

	glBegin(GL_LINES);
	vertexInt(Position.X, Position.Y, width, height);

	float fac = 26.6;//calcFactor(length, deltaX, deltaY);
	//cout << fac << " " << length << endl;

	vertexInt(Position.X + Delta.X * fac, Position.Y + Delta.Y * fac, width, height);
	glEnd();
}

void Player::update(GLFWwindow* window, Map* map)
{
	if (glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE && map->validPosition(Position.X + Delta.X, Position.Y + Delta.Y))
	{
		Position += Delta;
	}
	if (glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE)
	{
		Angle -= RotationSpeed;
		if (Angle < 0)
		{
			Angle += 2 * PI;
		}
		
		Delta.X = cos(Angle) * MovementSpeed;
		Delta.Y = sin(Angle) * MovementSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE && map->validPosition(Position.X - Delta.X, Position.Y - Delta.Y))
	{
		Position -= Delta;
	}
	if (glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE)
	{
		Angle += RotationSpeed;
		if (Angle > 2 * PI)
		{
			Angle -= 2 * PI;
		}

		Delta.X = cos(Angle) * MovementSpeed;
		Delta.Y = sin(Angle) * MovementSpeed;
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

	cout << "Player x: " << Position.X << endl;
	cout << "Player y: " << Position.Y << endl;

	cout << "Player angle: " << Angle << endl;
	cout << "Player deltaX: " << Delta.X << endl;
	cout << "Player deltaY: " << Delta.Y << endl;
}
