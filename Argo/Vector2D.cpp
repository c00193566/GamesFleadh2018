#include "Vector2D.h"

Vector2f::Vector2f()
{
	this->x = Zero().x;
	this->y = Zero().y;
}

Vector2f::Vector2f(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2f & Vector2f::Add(const Vector2f & v)
{
	this->x += v.x;
	this->y += v.y;

	return *this;
}

Vector2f & Vector2f::Subtract(const Vector2f & v)
{
	this->x -= v.x;
	this->y -= v.y;

	return *this;
}

Vector2f & Vector2f::Multiply(const Vector2f & v)
{
	this->x *= v.x;
	this->y *= v.y;

	return *this;
}

Vector2f & Vector2f::Divide(const Vector2f & v)
{
	this->x /= v.x;
	this->y /= v.y;

	return *this;
}

Vector2f & Vector2f::operator+=(const Vector2f v)
{
	return this->Add(v);
}

Vector2f & Vector2f::operator-=(const Vector2f v)
{
	return this->Subtract(v);
}

Vector2f & Vector2f::operator*=(const Vector2f v)
{
	return this->Multiply(v);
}

Vector2f & Vector2f::operator/=(const Vector2f v)
{
	return this->Divide(v);
}

Vector2f & Vector2f::operator*(const int i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}

Vector2f & Vector2f::Zero()
{
	this->x = 0.0f;
	this->y = 0.0f;
	return *this;
}

Vector2f & Vector2f::Normalise()
{
	float L = Length();

	this->x /= L;
	this->y /= L;

	return *this;
}

float Vector2f::Length()
{
	return sqrtf(pow(this->x, 2) + pow(this->y, 2));
}

Vector2f & operator+(Vector2f & v1, const Vector2f & v2)
{
	return v1.Add(v2);
}

Vector2f & operator-(Vector2f & v1, const Vector2f & v2)
{
	return v1.Subtract(v2);
}

Vector2f & operator*(Vector2f & v1, const Vector2f & v2)
{
	return v1.Multiply(v2);
}

Vector2f & operator/(Vector2f & v1, const Vector2f & v2)
{
	return v1.Divide(v2);
}
