#pragma once
#include <iostream>
#include "Components.h"

/// <class>Factory</class>
/// <summary>
/// This class will be a complete abstract class
/// for three other classes to inherit from. These
/// class will be used to create four different types
/// of entities with the corresponding components;
/// Player entity, AI entity, Bullet entity and Tile
/// entity.
/// </summary>
/// <author>Jack Keogh</author>

class Factory
{
public:
	virtual void CreateEntity(EntityManager * EManager, SDL_Texture * Texture = nullptr, float x = 64, float y = 64,
		float w = 32, float h = 32) = 0;

protected:
	Factory() {};
};

class PlayerFactory : public Factory
{
public:
	PlayerFactory() {};
	void CreateEntity(EntityManager * EManager, SDL_Texture * Texture = nullptr, float x = 64, float y = 64, float w = 32, float h = 32) override;
};

class AIFactory : public Factory
{
public:
	AIFactory() {};
	void CreateEntity(EntityManager * EManager, SDL_Texture * Texture, float x = 64, float y = 64, float w = 32, float h = 32) override;
};

class BulletFactory : public Factory
{
	BulletFactory() {};
	void CreateEntity(EntityManager * EManager, SDL_Texture * Texture, float x = 64, float y = 64, float w = 32, float h = 32) override;
};

class TileFactory : public Factory
{
	TileFactory() {};
	void CreateEntity(EntityManager * EManager, SDL_Texture * Texture, float x = 64, float y = 64, float w = 32, float h = 32, string type = "Walkway");
};