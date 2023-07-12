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
}