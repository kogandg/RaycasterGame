#pragma once
#include "IPanel.h"
#include "Map.h"
#include "Player.h"
#include "Ray.h"

class MapViewPanel : public IPanel
{
public:
	MapViewPanel(Vector2 position, Vector2 size, Vector2 internalSize);
	void Draw(GLFWwindow* window) override;
	void GetInformation(Player p, Map m, vector<Ray> r);
private:
	Player player;
	Map map;
	vector<Ray> rays;

	void drawRays(int width, int height);
};

