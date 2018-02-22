#pragma once
#include <iostream>
#include "ECS.h"

/// <class>StatComponent</class>
/// <summary>
/// This component is used to keep track of health,
/// defence and power.
/// </summary>
/// <author>Jack Keogh</author>

class StatComponent : public Component
{
private:
	float m_power;
	float m_health;
	float m_maxhealth;
	float m_defence;

public:
	
	/// <summary>
	/// Default constructor with overload parameters available.
	/// </summary>
	/// <param name="p">float to define power.</param>
	/// <param name="h">float to define health and max health.</param>
	/// <param name="d">float to define defence.</param>
	StatComponent(float p = 0, float h = 100, float d = 0) :
		m_power(p), m_health(h), m_maxhealth(h), m_defence(d) {};

	/// <summary>
	/// Update override
	/// </summary>
	void Update() override
	{
		if (m_health <= 0.0f)
		{
			m_entity->setActive(false);
		}
	}

	/// <summary>
	/// setter fucntions
	/// </summary>
	void setHealth(float value) { m_health = value; };

	/// <summary>
	/// getter functions
	/// </summary>
	float getPower() { return m_power; };
	float getDefence() { return m_defence; };
	float getHealth() { return m_health; };
	float getMaxHealth() { return m_maxhealth; };

};