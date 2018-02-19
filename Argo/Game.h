#pragma once
#include <iostream>
#include <SDL.h>
#include <AssetHandler.h>
#include "SceneManager.h"
#include "LevelLoader.h"

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
	RenderSystem * m_renderer;
	SceneManager * m_sceneManager;

	bool m_running;

	// Used to handle SDL events.
	void LocalEvent();

	// Used to update member variables.
	void Update(float DT);

	// Used to render member variables.
	void Render();

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