#include "Collision.h"

void Collision::WallCollision(vector<Entity*> characters, vector<Entity*> walls)
{
	float bounce = 2;

	for (int character = 0; character < characters.size(); character++)
	{
		for (int wall = 0; wall < walls.size(); wall++)
		{
			// Check Collision using AABB
			// Left
			if (AABB(characters.at(character)->getComponent<ColliderComponent>().getLeft(),
				walls.at(wall)->getComponent<ColliderComponent>().getCollider()))
			{
				characters.at(character)->getComponent<TransformComponent>().setPosition(
					Vector2f(characters.at(character)->getComponent<TransformComponent>().position.x + bounce,
						characters.at(character)->getComponent<TransformComponent>().position.y));
			}

			// Up
			if (AABB(characters.at(character)->getComponent<ColliderComponent>().getTop(),
				walls.at(wall)->getComponent<ColliderComponent>().getCollider()))
			{
				characters.at(character)->getComponent<TransformComponent>().setPosition(
					Vector2f(characters.at(character)->getComponent<TransformComponent>().position.x,
						characters.at(character)->getComponent<TransformComponent>().position.y + bounce));
			}

			// Right
			if (AABB(characters.at(character)->getComponent<ColliderComponent>().getRight(),
				walls.at(wall)->getComponent<ColliderComponent>().getCollider()))
			{
				characters.at(character)->getComponent<TransformComponent>().setPosition(
					Vector2f(characters.at(character)->getComponent<TransformComponent>().position.x - bounce,
						characters.at(character)->getComponent<TransformComponent>().position.y));
			}

			// Down
			if (AABB(characters.at(character)->getComponent<ColliderComponent>().getBottom(),
				walls.at(wall)->getComponent<ColliderComponent>().getCollider()))
			{
				characters.at(character)->getComponent<TransformComponent>().setPosition(
					Vector2f(characters.at(character)->getComponent<TransformComponent>().position.x,
						characters.at(character)->getComponent<TransformComponent>().position.y - bounce));
			}
		}
	}
}

void Collision::BulletWallCollision(vector<Entity*> bullets, vector<Entity*> others)
{
	for (auto& bullet : bullets)
	{
		for (auto& object : others)
		{
			if (AABB(bullet->getComponent<ColliderComponent>().getCollider(),
				object->getComponent<ColliderComponent>().getCollider()))
			{
				bullet->setActive(false);
			}
		}
	}
}

bool Collision::AABB(SDL_Rect obj1, SDL_Rect obj2)
{
	if ((obj1.x >= obj2.x && obj1.x <= obj2.x + obj2.w) ||
		(obj1.x + obj1.w >= obj2.x && obj1.x + obj1.w <= obj2.x + obj2.w))
	{
		if ((obj1.y >= obj2.y && obj1.y <= obj2.y + obj2.h) ||
			(obj1.y + obj1.h >= obj2.y && obj1.y + obj1.h <= obj2.y + obj2.h))
		{
			return true;
		}
	}

	return false;
}
