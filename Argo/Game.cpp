#include "Game.h"

void Game::LocalEvent()
{
	m_sceneManager->EventScene();
}

void Game::Update(float DT)
{
	m_sceneManager->UpdateScene();
}

void Game::Render()
{
	RenderSystem::Clear();

	m_sceneManager->RenderScene();

	RenderSystem::Present();
}

Game::Game() :
	m_levelloader(string("GeneralGameData.json"))
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

Game::~Game()
{

}

void Game::Init()
{
	m_running = true;

	// Load JSON data
	m_levelloader.LoadAll();

	// AssetHandler initialise
	m_assets = AssetHandler::Instance();

	// RenderSystem initialise
	RenderSystem::Init("Argo");

	// Load in images
	for (map<string, string>::iterator iter = GameData::m_sprites.begin(); iter != GameData::m_sprites.end(); iter++)
	{
		m_assets->addTexture(iter->first, iter->second, RenderSystem::Renderer());
	}

	// Create scene manager
	m_sceneManager = new SceneManager;

	// Initialise scene
	m_sceneManager->LoadNextLevel();
}

void Game::Run()
{
	// Used to Calculate frame rate
	int FRAMES_PER_SECOND = 60;
	int FRAME_DELAY = 1000 / FRAMES_PER_SECOND;
	Uint32 START_FRAME = 0;
	int FRAME_TIME = 0;

	// Used for Delta Time
	Uint64 NOW = 0;
	Uint64 LAST = 0;
	float DT = 0;

	/// Game Loop
	while (m_running)
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		DT = static_cast<float>((NOW - LAST) * 1000 / SDL_GetPerformanceFrequency());

		START_FRAME = SDL_GetTicks();

		///
		LocalEvent();
		Update(DT);
		Render();
		///

		m_running = m_sceneManager->getScene()->Running();

		FRAME_TIME = SDL_GetTicks() - START_FRAME;

		if (FRAME_DELAY > FRAME_TIME)
		{
			SDL_Delay(FRAME_DELAY - FRAME_TIME);
		}
	}
}
