#include "Level1.h"

Level1::Level1()
{
	IsRunning = true;
}

void Level1::Initialise()
{
	// Get AssetHandler Instance;
	m_assets = AssetHandler::Instance();

	// Create entity manager
	m_entManager = new EntityManager;

	// Create the factories
	m_playerFactory = new PlayerFactory;
	m_wallFactory = new WallFactory;
	m_floorFactory = new FloorFactory;
	m_aiFactory = new AIFactory;
	m_pBulletFactory = new PlayerBulletFactory;

	// Create input system
	m_inputsystem = new InputSystem;

	// Load Level
	LoadLevel();

	// Create Player
	m_playerFactory->CreateEntity(m_entManager, m_assets->getTexture("HM"), 336, 336);
}

void Level1::LoadLevel()
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

void Level1::Update()
{
	m_entManager->Update();
	m_inputsystem->Update(m_entManager, m_entManager->getGroup(Groups::PlayerGroup), m_pBulletFactory);

	MovementSystem::ControlledMovement(m_entManager->getGroup(Groups::PlayerGroup));
	MovementSystem::BulletMovement(m_entManager->getGroup(Groups::PlayerBulletGroup));

	Collision::WallCollision(m_entManager->getGroup(Groups::PlayerGroup), m_entManager->getGroup(Groups::WallGroup));
	Collision::BulletWallCollision(m_entManager->getGroup(Groups::PlayerBulletGroup), m_entManager->getGroup(Groups::WallGroup));

	m_entManager->Refresh();
}

void Level1::Render()
{
	m_entManager->Draw();
}

void Level1::Event()
{
	SDL_Event localEvent;

	while (SDL_PollEvent(&localEvent))
	{
		// Check if quit is pressed
		if (localEvent.type == SDL_QUIT)
		{
			IsRunning = false;
			break;
		}

		// Input System
		m_inputsystem->KeyPressed(localEvent, m_entManager->getGroup(Groups::PlayerGroup));
		m_inputsystem->KeyReleased(localEvent, m_entManager->getGroup(Groups::PlayerGroup));
		m_inputsystem->MouseButton(localEvent);
		m_inputsystem->MouseMove(localEvent);
	}
}