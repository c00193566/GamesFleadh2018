#pragma once
#include <iostream>
#include <cmath>

using namespace std;

/// <summary>
/// Vector2f class controlling an x and y float coordinate.
/// </summary>
/// <author> Jack Keogh </author>

struct Vector2f
{
	float x;
	float y;

	Vector2f();
	Vector2f(float x, float y);

	Vector2f& Add(const Vector2f& v);
	Vector2f& Subtract(const Vector2f& v);
	Vector2f& Multiply(const Vector2f& v);
	Vector2f& Divide(const Vector2f& v);

	friend Vector2f& operator+(Vector2f& v1, const Vector2f& v2);
	friend Vector2f& operator-(Vector2f& v1, const Vector2f& v2);
	friend Vector2f& operator*(Vector2f& v1, const Vector2f& v2);
	friend Vector2f& operator/(Vector2f& v1, const Vector2f& v2);

	Vector2f& operator+=(const Vector2f v);
	Vector2f& operator-=(const Vector2f v);
	Vector2f& operator*=(const Vector2f v);
	Vector2f& operator/=(const Vector2f v);

	Vector2f& operator*(const int i);
	Vector2f& Zero();
	Vector2f& Normalise();
	float Length();
};