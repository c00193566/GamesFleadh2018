#include "MovementSystem.h"

void MovementSystem::ControlledMovement(vector<Entity*> &entity, float DT)
{
	for (int i = 0; i < entity.size(); i++)
	{
		auto& ent = entity.at(i);
		if (ent->getComponent<TransformComponent>().acceleration.Length() != 0)
		{
			ent->getComponent<TransformComponent>().acceleration.x *= 0.9;
			ent->getComponent<TransformComponent>().acceleration.y *= 0.9;
		}

		ent->getComponent<TransformComponent>().velocity = ent->getComponent<TransformComponent>().acceleration * ent->getComponent<TransformComponent>().speed;
		ent->getComponent<TransformComponent>().position += ent->getComponent<TransformComponent>().velocity;
	}
}

void MovementSystem::BulletMovement(vector<Entity*>& entity)
{
	for (int i = 0; i < entity.size(); i++)
	{
		auto& ent = entity.at(i);

		Vector2f vec = ent->getComponent<TransformComponent>().getVelocity() * ent->getComponent<TransformComponent>().speed;

		ent->getComponent<TransformComponent>().position += vec;
	}
}
