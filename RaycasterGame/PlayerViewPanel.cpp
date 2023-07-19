#include "PlayerViewPanel.h"

PlayerViewPanel::PlayerViewPanel(Vector2 position, Vector2 size, Vector2 internalSize) : IPanel(position, size, internalSize)
{

}

void PlayerViewPanel::Draw(GLFWwindow* window)
{
	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);
	drawRays(width, height);
}

void PlayerViewPanel::GetInformation(Player p, Map m, vector<Ray> r)
{
	player = p;
	map = m;
	rays = r;
}

void PlayerViewPanel::drawRays(int width, int height)
{
	float lineWidth = internalSize.X / rays.size();
	for (int r = 0; r < rays.size(); r++)
	{
		Ray ray = rays[r];
		float rayAngle = Vector2(ray.RayVector - player.Position).Angle();
		float cosAngle = player.Angle - rayAngle;
		normalizeAngle(cosAngle);

		float finalDist = distance(player.Position.X, player.Position.Y, ray.RayVector.X, ray.RayVector.Y) * cos(cosAngle);//fixes fisheye look

		float lineHeight = (map.squareSize * internalSize.Y) / finalDist;


		if (lineHeight > internalSize.Y)
		{
			lineHeight = internalSize.Y;
		}
		float lineOffset = ((internalSize.Y - lineHeight) / 2);

		glBegin(GL_QUADS);
		
		//walls
		glColor3f(1, 0, 0);
		makeVertex(r*lineWidth, lineOffset);
		makeVertex(r * lineWidth + lineWidth , lineOffset);
		makeVertex(r * lineWidth + lineWidth, lineHeight + lineOffset);
		makeVertex(r * lineWidth, lineHeight + lineOffset);

		//floor
		glColor3f(0.2, 0.2, 0.2);
		makeVertex(r * lineWidth, lineHeight + lineOffset);
		makeVertex(r * lineWidth + lineWidth, lineHeight + lineOffset);
		makeVertex(r * lineWidth + lineWidth, internalSize.Y);
		makeVertex(r * lineWidth, internalSize.Y);

		//ceiling
		glColor3f(0.4, 0.4, 0.4);
		makeVertex(r * lineWidth, 0);
		makeVertex(r * lineWidth + lineWidth, 0);
		makeVertex(r * lineWidth + lineWidth, lineOffset);
		makeVertex(r * lineWidth, lineOffset);

		glEnd();

		//glLineWidth(1);
		//glColor3f(0, 0, 0);
		//glBegin(GL_LINES);

		////top line
		//makeVertex(0, 0);
		//makeVertex(internalSize.X, 0);

		////bottom line
		//makeVertex(0, internalSize.Y);
		//makeVertex(internalSize.X, internalSize.Y);

		////left line
		//makeVertex(0, 0);
		//makeVertex(0, internalSize.Y);

		////right line
		//makeVertex(internalSize.X, 0);
		//makeVertex(internalSize.X, internalSize.Y);

		//glEnd();
	}
}
