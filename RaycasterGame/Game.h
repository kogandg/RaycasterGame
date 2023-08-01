#pragma once
#include <functional>

#include "Map.h"
#include "Player.h"
#include "Ray.h"
#include "IPanel.h"
#include "MapViewPanel.h"
#include "PlayerViewPanel.h"

using namespace std;
using namespace Helpers;

class Game
{
public:

	Game();

	Map getMap();
	Player getPlayer();
	vector<Ray> getRays();

	void Draw(GLFWwindow* window);
	void Update(GLFWwindow* window, float frameTime);

private:
	Map* map;
	Player* player;
	vector<Ray> rays;
	vector<IPanel*> panels;
	int fov;//in degrees
	int numRays;//horizontal resolution


	MapViewPanel* mapViewPanel;
	PlayerViewPanel* playerViewPanel;

	void calcRays(int maxGridDistance = 8);
	//void drawRays();
};

