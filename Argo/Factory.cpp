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
	player.addGroup(Groups::PlayerGroup);
}

//////////////////////////////////////////////////////////////

void AIFactory::CreateEntity(EntityManager * EManager, SDL_Texture * Texture, float x, float y,
	float w, float h)
{

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
