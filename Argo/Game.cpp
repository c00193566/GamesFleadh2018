#include "Game.h"

void Game::LocalEvent()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			m_running = false;
		}

		m_inputsystem->KeyPressed(event, m_entManager->getEntities());
		m_inputsystem->KeyReleased(event, m_entManager->getEntities());
		m_inputsystem->MouseMove(event);
	}
}

void Game::Update(float DT)
{
	m_entManager->Update();
	m_inputsystem->Update(m_entManager->getEntities());

	MovementSystem::ControlledMovement(m_entManager->getEntities(), DT);
}

void Game::Render()
{
	RenderSystem::Clear();

	m_entManager->Draw();

	RenderSystem::Present();
}

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

Game::~Game()
{

}

void Game::Init()
{
	m_running = true;
	m_assets = AssetHandler::Instance();

	RenderSystem::Init("Argo");
	m_inputsystem = new InputSystem;

	m_entManager = new EntityManager;
	m_playerFactory = new PlayerFactory;

	m_playerFactory->CreateEntity(m_entManager);
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

		FRAME_TIME = SDL_GetTicks() - START_FRAME;

		if (FRAME_DELAY > FRAME_TIME)
		{
			SDL_Delay(FRAME_DELAY - FRAME_TIME);
		}
	}
}
