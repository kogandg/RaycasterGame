#pragma once
#include "Vector2.h"
class Ray
{
public:
	Vector2 Position;
	Vector2 RayVector;	
	
	
	Ray(Vector2 position, float rayX, float rayY);
	Ray(float rayX, float rayY);
	Ray(Vector2 position, Vector2 ray); 
	Ray(Vector2 ray);
	Ray();

	float Angle();
	float Length();
	Vector2 RayEnd();
};

