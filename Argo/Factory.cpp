#include "Factory.h"

void PlayerFactory::CreateEntity(EntityManager * EManager, SDL_Texture * Texture, float x, float y,
	float w, float h)
{
	auto& player = EManager->addEntity("player");
	player.addComponent<TransformComponent>(Vector2f(x, y), w, h, 0, 1, 1, 2);
	player.addComponent<SpriteComponent>("Assets/MachineGun.png", 43, 43);
	player.addComponent<CommandComponent>();
	player.addComponent<KeyComponent>(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
	player.addComponent<ColliderComponent>();
}

//////////////////////////////////////////////////////////////

void AIFactory::CreateEntity(EntityManager * EManager, SDL_Texture * Texture, float x, float y,
	float w, float h)
{

}

//////////////////////////////////////////////////////////////

void BulletFactory::CreateEntity(EntityManager * EManager, SDL_Texture * Texture, float x, float y,
	float w, float h)
{

}

//////////////////////////////////////////////////////////////

void TileFactory::CreateEntity(EntityManager * EManager, SDL_Texture * Texture, float x, float y,
	float w, float h, string type)
{

}
