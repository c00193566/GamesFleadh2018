#pragma once
#include <iostream>
#include "ECS.h"
#include "TransformComponent.h"
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
	TransformComponent * m_transform;
	vector<Vector2f> m_path;
	bool m_attarget;

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
	/// Component override for initialiser
	/// </summary>
	void Init() override;

	/// <summary>
	/// Component override for update
	/// </summary>
	void Update() override;

	/// <summary>
	/// Default deconstructor.
	/// </summary>
	~AIComponent() {};

	/// <summary>
	/// This function will be used to find a target.
	/// </summary>
	/// <param name="possibleTargets"></param>
	void findTarget(vector<Entity*> possibleTargets);

	/// <summary>
	/// setter functions
	/// </summary>
	void setTarget(Vector2f Target) { m_target = Target; };
	void setPath(vector<Vector2f> path) { m_path = path; };
	void setAtTarget(bool value) { m_attarget = value; };

	/// <summary>
	/// getter function
	/// </summary>
	Vector2f getTarget() { return m_target; };
	AITypes getType() { return m_type; };
	vector<Vector2f> getPath() { return m_path; };
	bool getAtTarget() { return m_attarget; };
};