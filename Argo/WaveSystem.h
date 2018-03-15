#pragma once
#include <iostream>
#include <AssetHandler.h>
#include "Factory.h"
#include "Components.h"

/// <class>WaveSystem</class>
/// <summary>
/// This system will control the spawning 
/// of enemies at set intervals.
/// </summary>
/// <author>Jack Keogh</author>

class WaveSystem
{
private:
	enum Flag
	{
		WAVE_START,
		WAVE_END
	};

	Flag m_flag;
	float m_timer;
	float m_spawntime;
	float m_wavetime;
	int m_aitospawn;
	int m_enemies;
	int m_wave;
	AssetHandler * m_assets;
	vector<Vector2f> m_spawnpoints;
	vector<Entity*> m_doors;

public:
	WaveSystem();
	~WaveSystem();

	void SpawnPointSetup(vector<Entity*> doors);
	void Update(vector<Entity*> enemies, Factory * AIfactory, EntityManager * m_entman);
	void Timer();
	void FlagUpdate();
	void Spawn(vector<Entity*> enemies, Factory * AIfactory, EntityManager * m_entman);

	int getWave() { return m_wave; };
};