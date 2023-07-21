#include "Ray.h"

Ray::Ray(Vector2 position, Vector2 end)
{
	Position = position;
	End = end;
}

Ray::Ray(Vector2 position, float endX, float endY) : Ray(position, Vector2(endX, endY))
{
}

Ray::Ray(Vector2 position) : Ray(position, position)
{
}

Ray::Ray() : Ray(Vector2::Zero())
{
}

Vector2 Ray::Vector()
{
	return End - Position;
}

float Ray::Angle()
{
	return Vector().Angle();
}

float Ray::Length()
{
	return Vector().Length();
}
