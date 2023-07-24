#include "Player.h"

Player::Player(Vector2 position, float movementSpeed, float rotationSpeed)
{
	Position = Vector2(position);
	MovementSpeed = movementSpeed;
	RotationSpeed = rotationSpeed;

	Angle = 0;
	delta = Vector2(cos(Angle) * movementSpeed, sin(Angle) * movementSpeed);
}

//Player::Player(int x, int y, float movementSpeed, float rotationSpeed) : Player(Vector2(x, y), movementSpeed, rotationSpeed) { }

//float length = 20;
//float lengthSpeed = 0.01;
//float calcFactor(float desiredLength, float x, float y)
//{
//	return desiredLength / (sqrt(x*x + y*y));
//}

void Player::Draw(function<void(Vector2)> makeVertex)// int width, int height)
{
	glPointSize(8);//need to set point size before begin
	glColor3f(1, 1, 0);

	glBegin(GL_POINTS);
	makeVertex(Position);
	//vertexInt(Position.X, Position.Y, width, height);
	glEnd();

	glLineWidth(3);

	glBegin(GL_LINES);
	makeVertex(Position);
	//vertexInt(Position.X, Position.Y, width, height);

	float fac = 26.6;//calcFactor(length, deltaX, deltaY);
	//cout << fac << " " << length << endl;
	makeVertex(Position + delta * fac);
	//vertexInt(Position.X + delta.X * fac, Position.Y + delta.Y * fac, width, height);
	glEnd();
}

void Player::update(GLFWwindow* window, function<bool(float, float)> validatePosition)//bool (*validatePosition) (float, float))//Map* map)
{
	if (glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE && validatePosition(Position.X + delta.X*5, Position.Y + delta.Y*5))//map->validPosition(Position.X + delta.X, Position.Y + delta.Y))
	{
		Position += delta;
	}
	if (glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE)
	{
		Angle -= RotationSpeed;
		if (Angle < 0)
		{
			Angle += 2 * PI;
		}
		
		delta.X = cos(Angle) * MovementSpeed;
		delta.Y = sin(Angle) * MovementSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE && validatePosition(Position.X - delta.X*5, Position.Y - delta.Y*5))//map->validPosition(Position.X - delta.X, Position.Y - delta.Y))
	{
		Position -= delta;
	}
	if (glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE)
	{
		Angle += RotationSpeed;
		if (Angle > 2 * PI)
		{
			Angle -= 2 * PI;
		}

		delta.X = cos(Angle) * MovementSpeed;
		delta.Y = sin(Angle) * MovementSpeed;
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
	cout << "Player deltaX: " << delta.X << endl;
	cout << "Player deltaY: " << delta.Y << endl;
}
