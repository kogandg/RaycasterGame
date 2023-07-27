#include "PlayerViewPanel.h"

PlayerViewPanel::PlayerViewPanel(Vector2 position, Vector2 size, Vector2 internalSize) : IPanel(position, size, internalSize)
{
	wallTexture = Texture2D("bitMap.bmp");
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
		float rayAngle = ray.Angle() - player.Angle;
		float cosAngle = rayAngle;
		normalizeAngle(cosAngle);

		float finalDist = ray.Length() * cos(cosAngle);//fixes fisheye look

		float lineHeight = internalSize.Y * map.squareSize / finalDist;

		float lineOffsetFromZero = (lineHeight - internalSize.Y) / 2;

		float yPerTexturePixel = lineHeight / wallTexture.Size.Y;

		int textureYStartOffSet = lineOffsetFromZero / yPerTexturePixel;

		if (textureYStartOffSet > (wallTexture.Size.Y / 2)-1)
		{
			cout << endl;
		}

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

		
		//int textX = wallX / xPerTexturePixel;
		/*if (ray.Angle() < PI)
		{
			int old = textX;
			textX = wallTexture.Size.X - textX-1;
			if (textX < 0 || textX >= wallTexture.Size.X)
			{
				cout << endl;
			}
		}*/
		/*if (ray.Angle() > P2 && ray.Angle() < P3)
		{
			textX = wallTexture.Size.X - textX - 1;
		}*/


		for (int textY = textureYStartOffSet; textY < wallTexture.Size.Y - textureYStartOffSet; textY++)
		{
			float yStart = yPerTexturePixel * textY - lineOffsetFromZero;
			float yEnd = yPerTexturePixel * (textY + 1) - lineOffsetFromZero;

			Vector2 texturePosition = Vector2(textX, textY);

			Color color = wallTexture.GetPixel(texturePosition);

			glColor3f(color.R, color.G, color.B);

			glBegin(GL_TRIANGLES);
			makeVertex(r * lineWidth, yStart);
			makeVertex(r * lineWidth + lineWidth, yStart);
			makeVertex(r * lineWidth, yEnd);


			makeVertex(r * lineWidth, yEnd);
			makeVertex(r * lineWidth + lineWidth, yEnd);
			makeVertex(r * lineWidth + lineWidth, yStart);
			glEnd();
		}

		//oldStuff

		//float lineHeight = (map.squareSize * internalSize.Y) / finalDist;


		//float yStep = lineHeight / wallTexture.Size.Y;
		//float yOff = 0;


		//if (lineHeight > internalSize.Y)
		//{
		//	yOff = (lineHeight - internalSize.Y) / 2.0f / 32.0f;

		//	lineHeight = internalSize.Y;
		//}

		//float lineOffset = ((internalSize.Y - lineHeight) / 2);

		////Vector2 mapPos = Vector2((int)(ray.End.X) / map.squareSize, (int)(ray.End.Y) / map.squareSize);

		///*float textureYStep = wallTexture.Size.Y / lineHeight;
		//float screenY = 0;
		//float yStep = textureYStep * wallTexture.Size.Y;*/

		//
		//Color color = wallTexture.GetPixel(Vector2(0, yOff));
		//for (int textY = yOff; textY < wallTexture.Size.Y; textY++)
		//{
		//	
		//	glColor3f(color.R, color.G, color.B);
		//	//glColor3f(1, 0, 0);
		//	glBegin(GL_TRIANGLES);
		//	makeVertex(r * lineWidth, lineOffset + (textY-yOff) * yStep);
		//	makeVertex(r * lineWidth + lineWidth, lineOffset + (textY - yOff) * yStep);
		//	makeVertex(r * lineWidth, lineOffset + (textY - yOff) * yStep + yStep);


		//	makeVertex(r * lineWidth, lineOffset + (textY - yOff) * yStep + yStep);
		//	makeVertex(r * lineWidth + lineWidth, lineOffset + (textY - yOff) * yStep + yStep);
		//	makeVertex(r * lineWidth + lineWidth, lineOffset + (textY - yOff) * yStep);
		//	glEnd();
		//	color = wallTexture.GetPixel(Vector2(0, textY));
		//}

		///*while (screenY < lineHeight + yStep)
		//{
		//	glColor3f(1, 0, 0);

		//	makeVertex(r * lineWidth, lineOffset + screenY);
		//	makeVertex(r * lineWidth + lineWidth, lineOffset + screenY);

		//	makeVertex(r * lineWidth, lineOffset + screenY + yStep);
		//	makeVertex(r * lineWidth + lineWidth, lineOffset + screenY + yStep);

		//	textureY += textureYStep;
		//	screenY += yStep;
		//}
		//glEnd();*/

		////for (int y = 0; y < lineHeight; y++)
		////{
		////	//Color color = wallTexture.GetPixel(Vector2(textureY, 0));
		////	//walls
		////	glColor3f(1, 0, 0);
		////	//glColor3f(color.R, color.G, color.B);

		////	//top verts
		////	makeVertex(r * lineWidth, lineOffset+y);
		////	makeVertex(r * lineWidth + lineWidth, lineOffset+y);

		////	//bottom verts
		////	makeVertex(r * lineWidth, lineOffset + y+1);
		////	makeVertex(r * lineWidth + lineWidth, lineOffset + y+1);
		////	/*makeVertex(r * lineWidth + lineWidth, lineHeight + lineOffset);
		////	makeVertex(r * lineWidth, lineHeight + lineOffset);*/
		////	textureY += textureYStep;
		////	/*if (textureY > 15)
		////	{
		////		cout << endl;
		////	}*/
		////}

		////floor
		////glColor3f(0.2, 0.2, 0.2);
		////makeVertex(r * lineWidth, lineHeight + lineOffset);
		////makeVertex(r * lineWidth + lineWidth, lineHeight + lineOffset);
		////makeVertex(r * lineWidth + lineWidth, internalSize.Y);
		////makeVertex(r * lineWidth, internalSize.Y);

		//////ceiling
		////glColor3f(0.4, 0.4, 0.4);
		////makeVertex(r * lineWidth, 0);
		////makeVertex(r * lineWidth + lineWidth, 0);
		////makeVertex(r * lineWidth + lineWidth, lineOffset);
		////makeVertex(r * lineWidth, lineOffset);

		////glEnd();

		////glLineWidth(1);
		////glColor3f(0, 0, 0);
		////glBegin(GL_LINES);

		//////top line
		////makeVertex(0, 0);
		////makeVertex(internalSize.X, 0);

		//////bottom line
		////makeVertex(0, internalSize.Y);
		////makeVertex(internalSize.X, internalSize.Y);

		//////left line
		////makeVertex(0, 0);
		////makeVertex(0, internalSize.Y);

		//////right line
		////makeVertex(internalSize.X, 0);
		////makeVertex(internalSize.X, internalSize.Y);

		////glEnd();
	}
}
