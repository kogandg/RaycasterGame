#pragma once
#include <math.h>
#include "Helpers.h"
using namespace Helpers;
class Vector2
{
public:
	float X;
	float Y;

	Vector2(float x, float y);
	Vector2(const Vector2& v);
	Vector2();

	static Vector2 Zero();
	static Vector2 One();
	static Vector2 UnitX();
	static Vector2 UnitY();

	float Angle();
	float Length();

	void RoundX(float round);
	void RoundY(float round);
	void Round(float round);

	void RoundXInt(int round);
	void RoundYInt(int round);
	void RoundInt(int round);

	Vector2 operator+(const Vector2& obj);
	Vector2 operator-(const Vector2& obj);
	Vector2 operator*(const Vector2& obj);
	Vector2 operator/(const Vector2& obj);
	Vector2 operator+(const float& obj);
	Vector2 operator-(const float& obj);
	Vector2 operator*(const float& obj);
	Vector2 operator/(const float& obj);

	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs);
	Vector2& operator*=(const Vector2& rhs);
	Vector2& operator/=(const Vector2& rhs);
	Vector2& operator+=(const float& rhs);
	Vector2& operator-=(const float& rhs);
	Vector2& operator*=(const float& rhs);
	Vector2& operator/=(const float& rhs);

	bool operator==(const Vector2& rhs);
	bool operator!=(const Vector2& rhs);
};

