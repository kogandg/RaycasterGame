#include <GLFW/glfw3.h>
#include <iostream>
#include <limits>
#include <string>

#include "Helpers.h"
#include "Game.h"

using namespace std;
//using namespace Helpers;

int windowWidth = 1024;
int windowHeight = 512;

float frame1;
float frame2;
float frameTime;

Game* game;

void init(GLFWwindow* window)
{
	glClearColor(0.3, 0.3, 0.3, 0);
	glfwSetWindowSize(window, windowWidth, windowHeight);

	//glfwWindowHint(GLFW_SAMPLES, 10);

	frame1 = 0;
	frame2 = 0;
	frameTime = 0;

	game = new Game();
}

void update(GLFWwindow* window)
{
	frame2 = glfwGetTime() * 1000;
	frameTime = frame2 - frame1;
	frame1 = glfwGetTime() * 1000;
	glfwSetWindowTitle(window, to_string(frameTime).c_str());

	game->Update(window, frameTime);
	
}

void draw(GLFWwindow* window)
{
	glClearColor(0.3, 0.3, 0.3, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game->Draw(window);

	glfwSwapBuffers(window);
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

