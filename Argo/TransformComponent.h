#pragma once
#include <iostream>
#include "ECS.h"
#include "Vector2D.h"

/// <class> TransformComponent <class>
/// <summary>
/// This component will handle the coordinates,
/// scale and velocity of an entiry.
/// </summary>
/// <author> Jack Keogh </author>

using namespace std;

class TransformComponent : public Component
{
public:
	Vector2f position;
	Vector2f velocity;
	Vector2f acceleration;

	int MaxAccel;
	int width;
	int height;
	int scale;
	float speed;
	float rotation;

	/// <summary>
	/// Overload constructor for transform component. All values
	/// will default to 0.
	/// </summary>
	/// <param name="p">Vector2f for position coords.</param>
	/// <param name="w">int to determine width.</param>
	/// <param name="h">int to determine height.</param>
	/// <param name="r">float to determine rotation.</param>
	/// <param name="s">int to determine scale.</param>
	/// <param name="v">int to determine speed.</param>
	/// /// <param name="a">int to determine max acceleration.</param>
	TransformComponent(Vector2f p = Vector2f(0, 0), int w = 0, int h = 0, float r = 0, int s = 0, int v = 0, int a = 0) :
		position(p),
		width(w),
		height(h),
		rotation(r),
		scale(s),
		speed(v),
		MaxAccel(a)
	{
		acceleration = Vector2f(0.0f, 0.0f);
	}

	void Init() override
	{
		velocity.Zero();
	}

	Vector2f getVelocity() { return velocity; };

	void setPosition(Vector2f value) { position = value; };
	void setVelocity(Vector2f value) { velocity = value; };
	void setAcceleration(Vector2f value) { acceleration = value; };
};