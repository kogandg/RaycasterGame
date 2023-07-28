#include "PlayerViewPanel.h"

PlayerViewPanel::PlayerViewPanel(Vector2 position, Vector2 size, Vector2 internalSize) : IPanel(position, size, internalSize)
{
	wallTexture = Texture2D("greystone.bmp");//("bitMap.bmp");
	bitMap = Texture2D("bitMap.bmp");
}

void PlayerViewPanel::Draw(GLFWwindow* window)
{
	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);
	drawRays(width, height);
	//drawOutline(width, height);
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
	
	//draw floors
	Ray firstRay = rays[0];
	Ray lastRay = rays[rays.size() - 1];

	for (int y = 0; y < internalSize.Y; y++)
	{
		int position = (internalSize.Y/2) - y;
		float zPosition = internalSize.Y / 2;

		float rowDistance = zPosition / position;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (lastRay.End.X - firstRay.End.X) / internalSize.X;
		float floorStepY = rowDistance * (lastRay.End.Y - firstRay.End.Y) / internalSize.X;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = player.Position.X + rowDistance * firstRay.End.X;
		float floorY = player.Position.Y + rowDistance * firstRay.End.Y;

		for (int x = 0; x < internalSize.X; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(bitMap.Size.X * (floorX - cellX)) & ((int)bitMap.Size.X - 1);
			int ty = (int)(bitMap.Size.Y * (floorY - cellY)) & ((int)bitMap.Size.Y - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			Color color;

			// floor
			color = bitMap.GetPixel(Vector2(tx, ty));
			//buffer[y][x] = color;

			////ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			//color = texture[ceilingTexture][texWidth * ty + tx];
			//color = (color >> 1) & 8355711; // make a bit darker
			//buffer[screenHeight - y - 1][x] = color;

			glPointSize(2);

			glColor3f(color.R, color.G, color.B);

			glBegin(GL_POINTS);

			makeVertex(Vector2(x, y));
			makeVertex(Vector2(x, internalSize.Y-y-1));

			glEnd();
		}
	}

	//draw walls
	//for (int r = 0; r < rays.size(); r++)
	//{
	//	Ray ray = rays[r];
	//	float rayAngle = ray.Angle() - player.Angle;
	//	float cosAngle = rayAngle;
	//	normalizeAngle(cosAngle);

	//	float finalDist = ray.Length() * cos(cosAngle);//fixes fisheye look
	//	float lineHeight = internalSize.Y * map.squareSize / finalDist;
	//	float lineOffsetFromZero = (lineHeight - internalSize.Y) / 2;

	//	float yPerTexturePixel = lineHeight / wallTexture.Size.Y;
	//	int textureYStartOffSet = lineOffsetFromZero / yPerTexturePixel;
	//	if (textureYStartOffSet < 0)
	//	{
	//		textureYStartOffSet = 0;
	//	}

	//	float xPerTexturePixel = map.squareSize / wallTexture.Size.X;
	//	int wallX;
	//	int textX;
	//	if (ray.HitVertical)
	//	{
	//		wallX = (int)(ray.End.Y) % map.squareSize;
	//		textX = wallX / xPerTexturePixel;
	//		if (ray.Angle() > P2 && ray.Angle() < P3)
	//		{
	//			textX = wallTexture.Size.X - textX - 1;
	//		}
	//	}
	//	else
	//	{
	//		wallX = (int)(ray.End.X) % map.squareSize;
	//		textX = wallX / xPerTexturePixel;
	//		if (ray.Angle() < PI)
	//		{
	//			textX = wallTexture.Size.X - textX - 1;
	//		}
	//	}

	//	/*float colorFactor = (1.0f/finalDist)*200;
	//	if (colorFactor > 1)
	//	{
	//		colorFactor = 1;
	//	}*/

	//	//draw walls
	//	for (int textY = textureYStartOffSet; textY < wallTexture.Size.Y - textureYStartOffSet; textY++)
	//	{
	//		Vector2 texturePosition = Vector2(textX, textY);
	//		Color color = wallTexture.GetPixel(texturePosition);
	//		/*color.R *= colorFactor;
	//		color.G *= colorFactor;
	//		color.B *= colorFactor;*/
	//		glColor3f(color.R, color.G, color.B);

	//		float yStart = yPerTexturePixel * textY - lineOffsetFromZero;
	//		float yEnd = yPerTexturePixel * (textY + 1) - lineOffsetFromZero;

	//		glBegin(GL_TRIANGLES);

	//		makeVertex(r * lineWidth, yStart);
	//		makeVertex(r * lineWidth + lineWidth, yStart);
	//		makeVertex(r * lineWidth, yEnd);


	//		makeVertex(r * lineWidth, yEnd);
	//		makeVertex(r * lineWidth + lineWidth, yEnd);
	//		makeVertex(r * lineWidth + lineWidth, yStart);

	//		glEnd();
	//	}
	//}
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
