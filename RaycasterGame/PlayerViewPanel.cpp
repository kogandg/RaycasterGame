#include "PlayerViewPanel.h"

PlayerViewPanel::PlayerViewPanel(Vector2 position, Vector2 size, Vector2 internalSize) : IPanel(position, size, internalSize)
{
	wallTexture = Texture2D("greystone.bmp");//("bitMap.bmp");
}

void PlayerViewPanel::Draw(GLFWwindow* window)
{
	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);
	drawRays(width, height);
	drawOutline(width, height);
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

	//draw floor
	

	//draw walls
	for (int r = 0; r < rays.size(); r++)
	{
		Ray ray = rays[r];
		float rayAngle = ray.Angle() - player.Angle;
		float cosAngle = rayAngle;
		normalizeAngle(cosAngle);

		float finalDist = ray.Length() * cos(cosAngle);//fixes fisheye look
		float lineHeight = internalSize.Y * map.squareSize / finalDist;
		float lineOffsetFromZero = (lineHeight - internalSize.Y) / 2;

		float yPerTexturePixel = lineHeight / wallTexture.Size.Y;
		int textureYStartOffSet = lineOffsetFromZero / yPerTexturePixel;
		if (textureYStartOffSet < 0)
		{
			textureYStartOffSet = 0;
		}

		float xPerTexturePixel = map.squareSize / wallTexture.Size.X;
		int wallX;
		int textX;
		if (ray.HitVertical)
		{
			wallX = (int)(ray.End.Y) % map.squareSize;
			textX = wallX / xPerTexturePixel;
			if (ray.Angle() > P2 && ray.Angle() < P3)
			{
				textX = wallTexture.Size.X - textX - 1;
			}
		}
		else
		{
			wallX = (int)(ray.End.X) % map.squareSize;
			textX = wallX / xPerTexturePixel;
			if (ray.Angle() < PI)
			{
				textX = wallTexture.Size.X - textX - 1;
			}
		}

		/*float colorFactor = (1.0f/finalDist)*200;
		if (colorFactor > 1)
		{
			colorFactor = 1;
		}*/

		//draw walls
		for (int textY = textureYStartOffSet; textY < wallTexture.Size.Y - textureYStartOffSet; textY++)
		{
			Vector2 texturePosition = Vector2(textX, textY);
			Color color = wallTexture.GetPixel(texturePosition);
			/*color.R *= colorFactor;
			color.G *= colorFactor;
			color.B *= colorFactor;*/
			glColor3f(color.R, color.G, color.B);

			float yStart = yPerTexturePixel * textY - lineOffsetFromZero;
			float yEnd = yPerTexturePixel * (textY + 1) - lineOffsetFromZero;

			glBegin(GL_TRIANGLES);

			makeVertex(r * lineWidth, yStart);
			makeVertex(r * lineWidth + lineWidth, yStart);
			makeVertex(r * lineWidth, yEnd);


			makeVertex(r * lineWidth, yEnd);
			makeVertex(r * lineWidth + lineWidth, yEnd);
			makeVertex(r * lineWidth + lineWidth, yStart);

			glEnd();
		}
	}
}

void PlayerViewPanel::drawOutline(int width, int height)
{
	glColor3f(0, 0, 0);
	glLineWidth(4);
	glBegin(GL_LINES);

	//top
	makeVertex(Vector2(0, 0));
	makeVertex(Vector2(internalSize.X, 0));

	//bottom
	makeVertex(Vector2(0, internalSize.Y));
	makeVertex(Vector2(internalSize.X, internalSize.Y));

	//left
	makeVertex(Vector2(0, 0));
	makeVertex(Vector2(0, internalSize.Y));

	//right
	makeVertex(Vector2(internalSize.X, 0));
	makeVertex(Vector2(internalSize.X, internalSize.Y));

	glEnd();
}
