#pragma once
#include <iostream>
#include "ECS.h"

/// <class>BulletComponent</class>
/// <summary>
/// This class controls how long a bullet
/// has to live. When the time runs out 
/// the bullet entity will be dead and 
/// m_alive will be set to false.
/// </summary>
/// <author>Jack Keogh</author>

using namespace std;

class BulletComponent : public Component
{
private:
	float m_timer;
	float m_timeToLive;
	bool alive;

public:
	/// <summary>
	/// Default constructor with an optional overload parameter.
	/// </summary>
	/// <param name="ttl">float defining time to live.</param>
	BulletComponent(float ttl = 0.0f) :
		m_timeToLive(ttl)
	{

	};

	void Init() override
	{
		m_timer = 0.0f;
	};

	void Update() override
	{
		m_timer += 1.0f / 60.0f;

		if (m_timer >= m_timeToLive)
		{
			m_entity->setActive(false);
		}
	}
};