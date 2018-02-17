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

		m_inputsystem->KeyPressed(event, m_entManager->getGroup(Groups::PlayerGroup));
		m_inputsystem->KeyReleased(event, m_entManager->getGroup(Groups::PlayerGroup));
		m_inputsystem->MouseMove(event);
		m_inputsystem->MouseButton(event);
	}
}

void Game::Update(float DT)
{
	m_entManager->Update();
	m_inputsystem->Update(m_entManager, m_entManager->getGroup(Groups::PlayerGroup), m_pBulletFactory);

	MovementSystem::ControlledMovement(m_entManager->getGroup(Groups::PlayerGroup), DT);
	MovementSystem::BulletMovement(m_entManager->getGroup(Groups::PlayerBulletGroup));

	Collision::WallCollision(m_entManager->getGroup(Groups::PlayerGroup), m_entManager->getGroup(Groups::WallGroup));
	Collision::BulletWallCollision(m_entManager->getGroup(Groups::PlayerBulletGroup), m_entManager->getGroup(Groups::WallGroup));

	m_entManager->Refresh();

}

void Game::Render()
{
	RenderSystem::Clear();

	m_entManager->Draw();

	RenderSystem::Present();
}

void Game::CreateLevel()
{
	int level = 0;

	vector<vector<int>> room = GameData::m_roomLayout.at(0);

	int x = 0;
	int y = 0;
	int width = 64, height = 64;

	for (int i = 0; i < room.size(); i++)
	{
		for (int j = 0; j < room.at(i).size(); j++)
		{
			x = j * width;
			y = i * height;

			// Horizontal Wall
			if (room.at(i).at(j) == 1)
			{
				m_wallFactory->CreateEntity(m_entManager, m_assets->getTexture("HorizontalWall"), x, y, width, height);
			}

			// Vertical Wall
			if (room.at(i).at(j) == 2)
			{
				m_wallFactory->CreateEntity(m_entManager, m_assets->getTexture("VerticalWall"), x, y, width, height);
			}

			// Top Left Wall
			if (room.at(i).at(j) == 3)
			{
				m_wallFactory->CreateEntity(m_entManager, m_assets->getTexture("TopLeftWall"), x, y, width, height);
			}

			// Top Right Wall
			if (room.at(i).at(j) == 4)
			{
				m_wallFactory->CreateEntity(m_entManager, m_assets->getTexture("TopRightWall"), x, y, width, height);
			}

			// Bottom Left Wall
			if (room.at(i).at(j) == 5)
			{
				m_wallFactory->CreateEntity(m_entManager, m_assets->getTexture("BottomLeftWall"), x, y, width, height);
			}

			// Bottom Right Wall
			if (room.at(i).at(j) == 6)
			{
				m_wallFactory->CreateEntity(m_entManager, m_assets->getTexture("BottomRightWall"), x, y, width, height);
			}

			// Basic Floor
			if (room.at(i).at(j) == 7)
			{
				m_floorFactory->CreateEntity(m_entManager, m_assets->getTexture("BasicFloor"), x, y, width, height);
			}

			// Cross Section Wall
			if (room.at(i).at(j) == 8)
			{
				m_wallFactory->CreateEntity(m_entManager, m_assets->getTexture("CrossSection"), x, y, width, height);
			}
		}
	}
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

	// InputSystem initialise
	m_inputsystem = new InputSystem;

	// EntityManager initialise
	m_entManager = new EntityManager;

	// Factories initialise
	m_playerFactory = new PlayerFactory;
	m_wallFactory = new WallFactory;
	m_floorFactory = new FloorFactory;
	m_aiFactory = new AIFactory;
	m_pBulletFactory = new PlayerBulletFactory;

	// Create Level
	CreateLevel();

	// Create player entity
	m_playerFactory->CreateEntity(m_entManager, m_assets->getTexture("HM"), 80, 80);

	// Create enemy entity
	m_aiFactory->CreateEntity(m_entManager, m_assets->getTexture("Zombie"), 472, 664);
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
