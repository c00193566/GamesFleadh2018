#include "AIComponent.h"

void AIComponent::Init()
{
	m_transform = &m_entity->getComponent<TransformComponent>();
	m_attarget = false;
}

void AIComponent::Update()
{
	Vector2f vel = m_transform->getVelocity();

	float rotation = atan2f(vel.x, -vel.y);

	rotation = rotation * 180 / 3.14;

	m_transform->rotation = rotation;

}

void AIComponent::findTarget(vector<Entity*> possibleTargets)
{
	float Distance = numeric_limits<float>::infinity() - 10000;
	Vector2f position = m_transform->position;

	for (Entity * e : possibleTargets)
	{
		if (e->hasComponent<TransformComponent>())
		{
			Vector2f possibleTarget = e->getComponent<TransformComponent>().position;

			Vector2f diff = possibleTarget - position;
			float dis = diff.Length();
			if (dis < Distance)
			{
				m_target = e->getComponent<TransformComponent>().position;
				Distance = dis;
			}
		}
	}
}
