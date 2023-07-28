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
	if (x < 0)
	{
		x = 0;
	}
	if (x >= internalSize.X)
	{
		x = internalSize.X;
	}
	if (y < 0)
	{
		y = 0;
	}
	if (y >= internalSize.Y)
	{
		y = internalSize.Y;
	}

	x = ((x / internalSize.X) * Size.X) + Position.X;
	y = ((y / internalSize.Y) * Size.Y) + Position.Y;
	vertexInt(x, y, 1024, 512);
}

void IPanel::makeVertex(Vector2 position)
{
	if (position.X < 0)
	{
		position.X = 0;
	}
	if (position.X >= internalSize.X)
	{
		position.X = internalSize.X;
	}
	if (position.Y < 0)
	{
		position.Y = 0;
	}
	if (position.Y >= internalSize.Y)
	{
		position.Y = internalSize.Y;
	}

	position = ((position / internalSize) * Size) + Position;
	vertexInt(position.X, position.Y, 1024, 512);
}
