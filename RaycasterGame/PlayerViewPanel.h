#pragma once
#include "IPanel.h"
#include "Map.h"
#include "Player.h"
#include "Ray.h"
#include "Texture2D.h"
class PlayerViewPanel : public IPanel
{
public:
	PlayerViewPanel(Vector2 position, Vector2 size, Vector2 internalSize);
	void Draw(GLFWwindow* window) override;
	void GetInformation(Player p, Map m, vector<Ray> r);
private:
	Player player;
	Map map;
	vector<Ray> rays;
	Texture2D wallTexture;

	void drawRays(int width, int height);
	void drawOutline(int width, int height);
};

