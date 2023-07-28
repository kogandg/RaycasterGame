#include "Player.h"

Player::Player(Vector2 position, float movementSpeed, float rotationSpeed)
{
	Position = Vector2(position);
	MovementSpeed = movementSpeed;
	RotationSpeed = rotationSpeed;

	Angle = 0;
	delta = Vector2(cos(Angle) * movementSpeed, sin(Angle) * movementSpeed);
}

void Player::Draw(function<void(Vector2)> makeVertex)
{
	glPointSize(8);
	glColor3f(1, 1, 0);

	glBegin(GL_POINTS);
	makeVertex(Position);
	glEnd();

	glLineWidth(3);

	glBegin(GL_LINES);
	makeVertex(Position);

	float fac = 26.6;
	makeVertex(Position + delta * fac);
	glEnd();
}

void Player::update(GLFWwindow* window, function<bool(float, float)> validatePosition, float frameTime)
{
	float moveSpeed = MovementSpeed * frameTime;
	float rotateSpeed = RotationSpeed * frameTime;
	if (getKeyState(window, GLFW_KEY_W) && validatePosition(Position.X + (delta.X * moveSpeed), Position.Y + (delta.Y * moveSpeed)))
	{
		Position += delta * moveSpeed;
	}
	if (getKeyState(window, GLFW_KEY_A))
	{
		Angle -= rotateSpeed;
		if (Angle < 0)
		{
			Angle += 2 * PI;
		}

		delta.X = cos(Angle);
		delta.Y = sin(Angle);
	}
	if (getKeyState(window, GLFW_KEY_S) && validatePosition(Position.X - (delta.X * moveSpeed), Position.Y - (delta.Y * moveSpeed)))
	{
		Position -= delta * moveSpeed;
	}
	if (getKeyState(window, GLFW_KEY_D))
	{
		Angle += rotateSpeed;
		if (Angle > 2 * PI)
		{
			Angle -= 2 * PI;
		}

		delta.X = cos(Angle);
		delta.Y = sin(Angle);
	}
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
