#include "Factory.h"

void PlayerFactory::CreateEntity(EntityManager * EManager, SDL_Texture * Texture, float x, float y,
	float w, float h)
{
	auto& player = EManager->addEntity();
	player.addComponent<TransformComponent>(Vector2f(x, y), w, h, 0, 1, 1, 2);
	player.addComponent<SpriteComponent>(Texture, 43, 43);
	player.addComponent<CommandComponent>();
	player.addComponent<KeyComponent>(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
	player.addComponent<ColliderComponent>();
	player.addComponent<WeaponComponent>(8, 0.2f, 1.0f);
	player.addComponent<StatComponent>(0, 100, 40);
	player.addComponent<HUDComponent>(m_assets->getTexture("HUD"), m_assets->getTexture("Health"));
	player.addGroup(Groups::PlayerGroup);
}

//////////////////////////////////////////////////////////////

void AIFactory::CreateEntity(EntityManager * EManager, SDL_Texture * Texture, float x, float y,
	float w, float h)
{
	auto& AI = EManager->addEntity();
	AI.addComponent<TransformComponent>(Vector2f(x, y), w, h, 0, 1, 1, 2);
	AI.addComponent<AIComponent>();
	AI.addComponent<CommandComponent>();
	AI.addComponent<SpriteComponent>(Texture, 43, 43);
	AI.addComponent<ColliderComponent>();
	AI.addComponent<StatComponent>(30, 50, 10);
	AI.addGroup(Groups::EnemyGroup);
}

//////////////////////////////////////////////////////////////

void PlayerBulletFactory::CreateEntity(EntityManager * EManager, SDL_Texture * Texture, float x, float y,
	float w, float h, float r)
{
	auto& bullet = EManager->addEntity();
	bullet.addComponent<TransformComponent>(Vector2f(x, y), w, h, r, 1, 6.0f, 2);
	bullet.addComponent<SpriteComponent>(Texture, 27, 47);
	bullet.addComponent<ColliderComponent>();
	bullet.addGroup(Groups::PlayerBulletGroup);
	bullet.addComponent<BulletComponent>(1.0f);
	bullet.addComponent<StatComponent>(40);
	Vector2f set = Vector2f(sin((r / 180 * 3.14f)), -cos((r / 180 * 3.14f)));

	set.Normalise();

	bullet.getComponent<TransformComponent>().setVelocity(set);
}

//////////////////////////////////////////////////////////////

void FloorFactory::CreateEntity(EntityManager * EManager, SDL_Texture * Texture, float x, float y,
	float w, float h)
{
	auto& floor = EManager->addEntity();
	floor.addComponent<TransformComponent>(Vector2f(x, y), w, h, 0, 1);
	floor.addComponent<SpriteComponent>(Texture, 96, 96);
	floor.addGroup(Groups::TileGroup);
}

//////////////////////////////////////////////////////////////

void WallFactory::CreateEntity(EntityManager * EManager, SDL_Texture * Texture, float x, float y, float w, float h)
{
	auto& wall = EManager->addEntity();
	wall.addComponent<TransformComponent>(Vector2f(x, y), w, h, 0, 1);
	wall.addComponent<SpriteComponent>(Texture, 96, 96);
	wall.addComponent<ColliderComponent>();
	wall.addGroup(Groups::WallGroup);
}

//////////////////////////////////////////////////////////////

void DoorFactory::CreateEntity(EntityManager * EManager, SDL_Texture * Texture, float x, float y, float w, float h)
{
	auto& door = EManager->addEntity();
	door.addComponent<TransformComponent>(Vector2f(x, y), w, h, 0, 1);
	door.addComponent<SpriteComponent>(Texture, 96, 96);
	door.addComponent<ColliderComponent>();
	door.addGroup(Groups::DoorGroup);
}
