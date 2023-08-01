#include "Helpers.h"

namespace Helpers
{
	void vertexInt(int x, int y, int width, int height)//to write point using pixel position, need to use map to map from pixels to -1 to 1
	{
		float xf = ((x / (float)width) * 2) - 1;//-1 is left, 1 is right
		float yf = -(((y / (float)height) * 2) - 1);//1 is top, -1 is bottom
		glVertex2f(xf, yf);
	}

	float distance(float ax, float ay, float bx, float by)
	{
		return sqrt((bx-ax)* (bx - ax) + (by-ay)* (by - ay));
	}

	void normalizeAngle(float &angle)
	{
		if (angle < 0)
		{
			angle += 2 * PI;
		}
		if (angle > 2 * PI)
		{
			angle -= 2 * PI;
		}
	}

	int readInt(unsigned char data[], int start)
	{
		unsigned int num;
		num = data[start] + (data[start + 1] << 8) + (data[start + 2] << 16) + (data[start + 3] << 24);
		return num;
	}

	bool getKeyState(GLFWwindow* window, int key)
	{
		return glfwGetKey(window, key) != GLFW_RELEASE;
	}
}