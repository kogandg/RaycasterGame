#pragma once
#include "Vector2.h"
class Ray
{
public:
	Vector2 Position;
	Vector2 End;
	bool HitVertical;
	
	Ray(Vector2 position, Vector2 end);
	Ray(Vector2 position, float endX, float endY);
	Ray(Vector2 position);
	Ray();

	Vector2 Vector();
	float Angle();
	float Length();
};

