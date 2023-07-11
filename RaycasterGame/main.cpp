#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

int windowWidth = 1024;
int windowHeight = 512;

float playerXPosition;
float playerYPosition;


void vertexInt(int x, int y)//to write point using pixel position, need to use map to map from pixels to -1 to 1
{
	float xf = ((x / (float)windowWidth) * 2) - 1;//-1 is left, 1 is right
	float yf = -(((y / (float)windowHeight) * 2) - 1);//1 is top, -1 is bottom
	glVertex2f(xf, yf);
}

void playerMovementButtons(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE)
	{
		playerYPosition -= 5;
	}
	if (glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE)
	{
		playerXPosition -= 5;
	}
	if (glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE)
	{
		playerYPosition += 5;
	}
	if (glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE)
	{
		playerXPosition += 5;
	}
}

void drawPlayer()
{
	glPointSize(8);//need to set point size before begin
	glColor3f(1, 1, 0);

	glBegin(GL_POINTS);
	vertexInt(playerXPosition, playerYPosition);
	glEnd();
}

void display(GLFWwindow* window)
{

	glClearColor(0.3, 0.3, 0.3, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	drawPlayer();
	glfwSwapBuffers(window);
}

void init(GLFWwindow* window)
{
	glClearColor(0.3, 0.3, 0.3, 0);
	glfwSetWindowSize(window, windowWidth, windowHeight);

	playerXPosition = 300;
	playerYPosition = 300;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(windowWidth, windowHeight, "Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		cout << "Failed window creation";
		return -1;
	}
	init(window);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		display(window);
		glfwSetKeyCallback(window, playerMovementButtons);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

