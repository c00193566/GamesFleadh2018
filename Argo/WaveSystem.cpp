#include "WaveSystem.h"

WaveSystem::WaveSystem()
{
	m_wave = 0;

	m_aitospawn = 0;
	m_enemies = 0;

	m_spawntime = 0.5f;
	m_wavetime = 2.0f;

	m_timer = m_wavetime;

	m_flag = Flag::WAVE_END;

	m_assets = AssetHandler::Instance();
}

WaveSystem::~WaveSystem()
{
}

void WaveSystem::SpawnPointSetup(vector<Entity*> doors)
{
	m_doors = doors;

	for (Entity * door : doors)
	{
		TransformComponent * T = &door->getComponent<TransformComponent>();
		Vector2f SpawnPos = T->getPosition();
		SpawnPos.x += 16;
		SpawnPos.y += 16;
		m_spawnpoints.push_back(SpawnPos);
	}
}

void WaveSystem::Update(vector<Entity*> enemies, Factory * AIfactory, EntityManager * m_entman)
{
	// Update timer
	Timer();

	// Update the flag
	FlagUpdate();
	
	// Update amount of enemies
	m_enemies = enemies.size();

	// Spawn an Enemy
	Spawn(enemies, AIfactory, m_entman);
}

void WaveSystem::Timer()
{
	m_timer -= 1.0f / 60.0f;
}

void WaveSystem::FlagUpdate()
{
	if (m_flag == Flag::WAVE_START)
	{
		if (m_enemies <= 0)
		{
			if (m_aitospawn <= 0)
			{
				m_flag = Flag::WAVE_END;
				m_timer = m_wavetime;
			}
		}
	}
	else
	{
		if (m_timer <= 0)
		{
			m_flag = Flag::WAVE_START;
			m_timer = m_spawntime;
			m_wave++;
			m_aitospawn = m_wave * 2;

			if (m_aitospawn > 14)
			{
				m_aitospawn = 14;
			}
		}
	}
}

void WaveSystem::Spawn(vector<Entity*> enemies, Factory * AIfactory, EntityManager * m_entman)
{
	if (m_flag == Flag::WAVE_START)
	{
		if (m_enemies < 10)
		{
			if (m_aitospawn > 0)
			{
				if (m_timer <= 0.0f)
				{
					int RandPos = rand() % m_spawnpoints.size();

					Vector2f pos = m_spawnpoints.at(RandPos);

					AIfactory->CreateEntity(m_entman, m_assets->getTexture("Zombie"), pos.x, pos.y);
					m_aitospawn--;
					m_timer = m_spawntime;
				}
			}
		}
	}
}
