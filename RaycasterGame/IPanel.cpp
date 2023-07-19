#include "IPanel.h"

IPanel::IPanel(Vector2 position, Vector2 size, Vector2 internalSize)
{
	Position = position;
	Size = size;
	this->internalSize = internalSize;
}

std::function<void(Vector2)> IPanel::getMakeVertex()
{
	return [&](Vector2 position) -> void { makeVertex(position); };
}

void IPanel::makeVertex(float x, float y)
{
	x = ((x / internalSize.X) * Size.X) + Position.X;
	y = ((y / internalSize.Y) * Size.Y) + Position.Y;
	vertexInt(x, y, 1024, 512);
}

void IPanel::makeVertex(Vector2 position)
{
	position = ((position / internalSize) * Size) + Position;
	vertexInt(position.X, position.Y, 1024, 512);
}
