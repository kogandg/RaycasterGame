#include "Vector2.h"

Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}

Vector2::Vector2(const Vector2& v)
{
	X = v.X;
	Y = v.Y;
}

Vector2::Vector2() : Vector2(0, 0) { }


Vector2 Vector2::Zero()
{
	return Vector2(0, 0);
}

Vector2 Vector2::One()
{
	return Vector2(1, 1);
}

Vector2 Vector2::UnitX()
{
	return Vector2(1, 0);
}

Vector2 Vector2::UnitY()
{
	return Vector2(0, 1);
}

Vector2 Vector2::operator+(const Vector2& obj)
{
	return Vector2(X + obj.X, Y + obj.Y);
}

Vector2 Vector2::operator-(const Vector2& obj)
{
	return Vector2(X - obj.X, Y - obj.Y);
}

Vector2 Vector2::operator*(const Vector2& obj)
{
	return Vector2(X * obj.X, Y * obj.Y);
}

Vector2 Vector2::operator/(const Vector2& obj)
{
	return Vector2(X / obj.X, Y / obj.Y);
}

Vector2 Vector2::operator+(const float& obj)
{
	return Vector2(X + obj, Y + obj);
}

Vector2 Vector2::operator-(const float& obj)
{
	return Vector2(X - obj, Y - obj);
}

Vector2 Vector2::operator*(const float& obj)
{
	return Vector2(X * obj, Y * obj);
}

Vector2 Vector2::operator/(const float& obj)
{
	return Vector2(X / obj, Y / obj);
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	*this = *this + rhs;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	*this = *this - rhs;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& rhs)
{
	*this = *this * rhs;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& rhs)
{
	*this = *this / rhs;
	return *this;
}

Vector2& Vector2::operator+=(const float& rhs)
{
	*this = *this + rhs;
	return *this;
}

Vector2& Vector2::operator-=(const float& rhs)
{
	*this = *this - rhs;
	return *this;
}

Vector2& Vector2::operator*=(const float& rhs)
{
	*this = *this * rhs;
	return *this;
}

Vector2& Vector2::operator/=(const float& rhs)
{
	*this = *this / rhs;
	return *this;
}

bool Vector2::operator==(const Vector2& rhs)
{
	return (X == rhs.X && Y == rhs.Y);
}

bool Vector2::operator!=(const Vector2& rhs)
{
	return !(*this == rhs);
}

