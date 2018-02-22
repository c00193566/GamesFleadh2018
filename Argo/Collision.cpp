#include "Collision.h"

void Collision::BounceCollision(vector<Entity*> characters, vector<Entity*> others)
{
	float bounce;

	if (characters.size() > 0)
	{
		if (characters.at(0)->hasGroup(Groups::PlayerGroup))
		{
			bounce = 2;
		}
		else
		{
			bounce = 5;
		}
	}

	for (int character = 0; character < characters.size(); character++)
	{
		for (int other = 0; other < others.size(); other++)
		{
			if (characters.at(character) == others.at(other))
			{
				break;
			}

			// Check Collision using AABB
			// Left
			if (AABB(characters.at(character)->getComponent<ColliderComponent>().getLeft(),
				others.at(other)->getComponent<ColliderComponent>().getCollider()))
			{
				characters.at(character)->getComponent<TransformComponent>().setPosition(
					Vector2f(characters.at(character)->getComponent<TransformComponent>().position.x + bounce,
						characters.at(character)->getComponent<TransformComponent>().position.y));
			}

			// Up
			if (AABB(characters.at(character)->getComponent<ColliderComponent>().getTop(),
				others.at(other)->getComponent<ColliderComponent>().getCollider()))
			{
				characters.at(character)->getComponent<TransformComponent>().setPosition(
					Vector2f(characters.at(character)->getComponent<TransformComponent>().position.x,
						characters.at(character)->getComponent<TransformComponent>().position.y + bounce));
			}

			// Right
			if (AABB(characters.at(character)->getComponent<ColliderComponent>().getRight(),
				others.at(other)->getComponent<ColliderComponent>().getCollider()))
			{
				characters.at(character)->getComponent<TransformComponent>().setPosition(
					Vector2f(characters.at(character)->getComponent<TransformComponent>().position.x - bounce,
						characters.at(character)->getComponent<TransformComponent>().position.y));
			}

			// Down
			if (AABB(characters.at(character)->getComponent<ColliderComponent>().getBottom(),
				others.at(other)->getComponent<ColliderComponent>().getCollider()))
			{
				characters.at(character)->getComponent<TransformComponent>().setPosition(
					Vector2f(characters.at(character)->getComponent<TransformComponent>().position.x,
						characters.at(character)->getComponent<TransformComponent>().position.y - bounce));
			}
		}
	}
}

void Collision::BulletWallCollision(vector<Entity*> bullets, vector<Entity*> Walls)
{
	for (auto& bullet : bullets)
	{
		for (auto& object : Walls)
		{
			if (AABB(bullet->getComponent<ColliderComponent>().getCollider(),
				object->getComponent<ColliderComponent>().getCollider()))
			{
				bullet->setActive(false);
			}
		}
	}
}

void Collision::BulletEntityCollision(vector<Entity*> bullets, vector<Entity*> entities)
{
	for (auto& bullet : bullets)
	{
		for (auto& entity : entities)
		{
			if (AABB(bullet->getComponent<ColliderComponent>().getCollider(),
				entity->getComponent<ColliderComponent>().getCollider()))
			{
				bullet->setActive(false);

				float damage = DamageCal(entity->getComponent<StatComponent>().getPower(),
					entity->getComponent<StatComponent>().getDefence());

				float health = entity->getComponent<StatComponent>().getHealth();

				health -= damage;

				entity->getComponent<StatComponent>().setHealth(health);
			}
		}
	}
}

void Collision::EnemyPlayerCollision(vector<Entity*> AI, vector<Entity*> players)
{
	float bounce = 5.0f;

	for (Entity * player : players)
	{
		for (Entity * enemy : AI)
		{
			bool collision = false;

			if (AABB(enemy->getComponent<ColliderComponent>().getLeft(),
				player->getComponent<ColliderComponent>().getCollider()))
			{
				enemy->getComponent<TransformComponent>().setPosition(
					Vector2f(enemy->getComponent<TransformComponent>().position.x + bounce,
						enemy->getComponent<TransformComponent>().position.y));
				collision = true;
			}

			// Up
			if (AABB(enemy->getComponent<ColliderComponent>().getTop(),
				player->getComponent<ColliderComponent>().getCollider()))
			{
				enemy->getComponent<TransformComponent>().setPosition(
					Vector2f(enemy->getComponent<TransformComponent>().position.x,
						enemy->getComponent<TransformComponent>().position.y + bounce));
				collision = true;
			}

			// Right
			if (AABB(enemy->getComponent<ColliderComponent>().getRight(),
				player->getComponent<ColliderComponent>().getCollider()))
			{
				enemy->getComponent<TransformComponent>().setPosition(
					Vector2f(enemy->getComponent<TransformComponent>().position.x - bounce,
						enemy->getComponent<TransformComponent>().position.y));
				collision = true;
			}

			// Down
			if (AABB(enemy->getComponent<ColliderComponent>().getBottom(),
				player->getComponent<ColliderComponent>().getCollider()))
			{
				enemy->getComponent<TransformComponent>().setPosition(
					Vector2f(enemy->getComponent<TransformComponent>().position.x,
						enemy->getComponent<TransformComponent>().position.y - bounce));
				collision = true;
			}

			if (collision)
			{
				float damage = DamageCal(enemy->getComponent<StatComponent>().getPower(),
					player->getComponent<StatComponent>().getDefence());

				float health = player->getComponent<StatComponent>().getHealth();

				health -= damage;

				player->getComponent<StatComponent>().setHealth(health);
			}
		}
	}
}

float Collision::DamageCal(float p, float d)
{
	float Damage;

	Damage = (p * 4.0f) / d;

	return Damage;
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
