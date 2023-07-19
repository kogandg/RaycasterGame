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
	int screenWidth = 160;
	int screenHeight = 320;
	int screenHeightOffset = 50;
	for (int r  = 0; r < rays.size(); r++)
	{
		Ray ray = rays[r];
		float rayAngle = Vector2(ray.RayVector - player.Position).Angle();
		float cosAngle = player.Angle - rayAngle;
		normalizeAngle(cosAngle);

		float finalDist = distance(player.Position.X, player.Position.Y, ray.RayVector.X, ray.RayVector.Y) * cos(cosAngle);//fixes fisheye look

		float lineHeight = (map.squareSize * screenHeight) / finalDist;


		if (lineHeight > 320)
		{
			lineHeight = 320;
		}
		float lineOffset = ((screenHeight - lineHeight) / 2) + screenHeightOffset;

		glLineWidth(8);
		glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		makeVertex(Vector2(r*8, lineOffset));
		makeVertex(Vector2(r*8, lineHeight + lineOffset));
		/*vertexInt(r * 8 + 530, lineOffset, width, height);
		vertexInt(r * 8 + 530, lineHeight + lineOffset, width, height);*/
		glEnd();

		/*glBegin(GL_LINES);
		glColor3f(0.2, 0.2, 0.2);
		vertexInt(530, screenHeight, windowWidth, windowHeight);
		vertexInt(530+screenWidth, screenHeight, windowWidth, windowHeight);

		vertexInt(r * 8 + 530, lineHeight + lineOffset, width, height);
		vertexInt(r * 8 + 530, screenHeight + screenHeightOffset, width, height);

		glColor3f(0.4, 0.4, 0.4);
		vertexInt(r * 8 + 530, screenHeightOffset, width, height);
		vertexInt(r * 8 + 530, lineOffset, width, height);
		glEnd();*/
	}
}
