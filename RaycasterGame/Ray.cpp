#include "Ray.h"

Ray::Ray(Vector2 position, float rayX, float rayY)
{
	Position = position;
	RayVector = Vector2(rayX, rayY);
}

Ray::Ray(float rayX, float rayY) : Ray(Vector2::Zero(), rayX, rayY)
{

}

Ray::Ray(Vector2 position, Vector2 ray) : Ray(position, ray.X, ray.Y)
{

}

Ray::Ray(Vector2 ray) : Ray(Vector2::Zero(), ray)
{

}

Ray::Ray() : Ray(Vector2::Zero())
{
}

float Ray::Angle()
{
	return RayVector.Angle();
}

float Ray::Length()
{
	return RayVector.Length();
}

Vector2 Ray::RayEnd()
{
	return Position + RayVector;
}
