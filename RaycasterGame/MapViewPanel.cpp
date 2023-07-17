#include "MapViewPanel.h"

MapViewPanel::MapViewPanel()
{
	//player = Player(Ve, 0, 0);
}

void MapViewPanel::Draw(GLFWwindow* window)
{
	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);
	map.draw(width, height);
	drawRays(width, height);
	player.Draw(width, height);
}

void MapViewPanel::GetInformation(Player p, Map m, vector<Ray> r)
{
	player = p;
	map = m;
	rays = r;
}

void MapViewPanel::drawRays(int width, int height)
{
	for (Ray ray : rays)
	{
		glLineWidth(1);
		glBegin(GL_LINES);
		vertexInt(player.Position.X, player.Position.Y, width, height);
		vertexInt(ray.RayVector.X, ray.RayVector.Y, width, height);
		glEnd();
	}
}
