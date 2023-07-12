#include <GLFW/glfw3.h>
#include <iostream>

#include "Helpers.h"
#include "Player.h"

using namespace std;
using namespace Helpers;

int windowWidth = 1024;
int windowHeight = 512;

Player* player;

void update(GLFWwindow* window)
{
	player->update(window);
}

void draw(GLFWwindow* window)
{

	glClearColor(0.3, 0.3, 0.3, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	player->draw(windowWidth, windowHeight);
	glfwSwapBuffers(window);
}

void init(GLFWwindow* window)
{
	glClearColor(0.3, 0.3, 0.3, 0);
	glfwSetWindowSize(window, windowWidth, windowHeight);

	player = new Player(300, 300, 1.5f);
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
		update(window);
		draw(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

