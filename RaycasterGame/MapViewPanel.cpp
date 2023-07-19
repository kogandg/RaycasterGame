#include "MapViewPanel.h"

MapViewPanel::MapViewPanel(Vector2 position, Vector2 size, Vector2 internalSize) : IPanel(position, size, internalSize) 
{

}

void MapViewPanel::Draw(GLFWwindow* window)
{
	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);
	map.draw(getMakeVertex());//[&](Vector2 position) -> void { makeVertex(position); });//width, height);
	drawRays(width, height);
	player.Draw(getMakeVertex());//[&](Vector2 position) -> void { makeVertex(position); });//width, height);
}

void MapViewPanel::GetInformation(Player p, Map m, vector<Ray> r)
{
	player = p;
	map = m;
	rays = r;
}

void MapViewPanel::drawRays(int width, int height)
{
	glLineWidth(1);
	glColor3f(0.5, 0.5, 0.5);
	for (Ray ray : rays)
	{
		
		glBegin(GL_LINES);
		
		makeVertex(player.Position);
		makeVertex(ray.RayVector);
		//vertexInt(player.Position.X, player.Position.Y, width, height);
		//vertexInt(ray.RayVector.X, ray.RayVector.Y, width, height);
		glEnd();
	}
}
