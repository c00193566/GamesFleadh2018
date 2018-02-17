#pragma once
#include <iostream>
#include <SDL.h>
#include <AssetHandler.h>
#include "LevelLoader.h"
#include "Components.h"
#include "Factory.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "MovementSystem.h"
#include "Collision.h"

///<summary>
/// The game class will handle the running of the game.
/// It will contain all major handlers and managers.
///</summary>
///<author> Jack Keogh</author>

using namespace std;

class Game
{
private:
	LevelLoader m_levelloader;
	AssetHandler * m_assets;
	EntityManager * m_entManager;
	RenderSystem * m_renderer;
	InputSystem * m_inputsystem;
	Factory * m_playerFactory;
	Factory * m_wallFactory;
	Factory * m_floorFactory;
	Factory * m_aiFactory;
	PlayerBulletFactory * m_pBulletFactory;

	bool m_running;

	// Used to handle SDL events.
	void LocalEvent();

	// Used to update member variables.
	void Update(float DT);

	// Used to render member variables.
	void Render();

	void CreateLevel();

public:
	Game();
	~Game();

	// Initialises member variables.
	void Init();

	// Runs the game loop.
	// Calculates delta time.
	// Limits frame rate.
	void Run();
};