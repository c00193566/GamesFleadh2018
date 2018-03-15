#pragma once
#include <iostream>
#include <AssetHandler.h>
#include "Scene.h"
#include "LevelLoader.h"
#include "Components.h"
#include "Factory.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "MovementSystem.h"
#include "Collision.h"
#include "AISystem.h"
#include "WaveSystem.h"

class Level1 : public Scene
{
private:
	// Asset Handler
	AssetHandler * m_assets;

	// Entity Manager
	EntityManager * m_entManager;

	// Input system
	InputSystem * m_inputsystem;

	// AI system
	AISystem * m_aisystem;

	// Wave system
	WaveSystem * m_wavesystem;

	// Factories
	Factory * m_playerFactory;
	Factory * m_wallFactory;
	Factory * m_floorFactory;
	Factory * m_aiFactory;
	Factory * m_doorFactory;
	PlayerBulletFactory * m_pBulletFactory;

public:
	Level1();
	~Level1() {};
	void Initialise();
	void LoadLevel();
	void Update();
	void Render();
	void Event();
	bool Running() { return IsRunning; };
};