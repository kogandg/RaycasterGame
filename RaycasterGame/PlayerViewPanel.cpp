#include "PlayerViewPanel.h"

PlayerViewPanel::PlayerViewPanel()
{
}

void PlayerViewPanel::Draw(GLFWwindow* window)
{
}

void PlayerViewPanel::GetInformation(Player p, Map m, vector<Ray> r)
{
	player = p;
	map = m;
	rays = r;
}

void PlayerViewPanel::drawRays(int width, int height)
{
}
