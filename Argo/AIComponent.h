#pragma once
#include <iostream>
#include "ECS.h"
#include "Vector2D.h"

/// <class>AiComponent</class>
/// <summary>
/// This component is designed for artifical intelligence,
/// it will keep track of two variables; AI type and target.
/// </summary>
/// <author>Jack Keogh</author>

enum AITypes : size_t
{
	Melee,
};

class AIComponent : public Component
{
private:
	Vector2f m_target;
	AITypes m_type;

public:
	/// <summary>
	/// Default constructor with overload paramaters available
	/// </summary>
	/// <param name="Type">The AI type.</param>
	/// <param name="Target"></param>
	AIComponent(AITypes Type = AITypes::Melee, Vector2f Target = Vector2f())
	{
		m_target = Target;
		m_type = Type;
	}

	/// <summary>
	/// Default deconstructor.
	/// </summary>
	~AIComponent() {};

	/// <summary>
	/// setter functions
	/// </summary>
	void setTarget(Vector2f Target) { m_target = Target; };

	/// <summary>
	/// getter function
	/// </summary>
	Vector2f getTarget() { return m_target; };
};