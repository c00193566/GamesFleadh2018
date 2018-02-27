#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "ECS.h"
#include "RenderSystem.h"
#include "Vector2D.h"
#include "WeaponComponent.h"
#include "StatComponet.h"

/// <class>HUDComponent</class>
/// <summary>
/// A component geared purely for 
/// player entity that creates a
/// heads up display relaying
/// health, armour, wave and 
/// clip size. 
/// </summary>
/// <author>Jack Keogh</author>

struct Bar
{
	SDL_Rect m_src;
	SDL_Rect m_dst;
	SDL_Texture * m_texture;
	float m_scale;
	float m_width;
	float m_maxwidth;
	float m_current;
};

class HUDComponent : public Component
{
private:
	Bar * HealthBar;
	SDL_Rect m_dst;
	SDL_Rect m_src;
	SDL_Texture * m_texture;
	WeaponComponent * m_weapon;
	StatComponent * m_stats;

public:
	/// <summary>
	/// Default constructor with overload parameter
	/// </summary>
	HUDComponent(SDL_Texture * sprite = nullptr, SDL_Texture * health = nullptr)
	{
		m_texture = sprite;
		m_dst = SDL_Rect{ 0, 768, 768, 128 };
		m_src = SDL_Rect{ 0, 0, 768, 128 };

		// Health Bar
		HealthBar = new Bar;
		HealthBar->m_dst = SDL_Rect{ 197, 798, 374, 19 };
		HealthBar->m_src = SDL_Rect{ 0, 0, 32, 32 };
		HealthBar->m_texture = health;
		HealthBar->m_width = 374.0f;
		HealthBar->m_maxwidth = 374.0f;
		HealthBar->m_scale = 1.0f;
	}

	/// <summary>
	/// override initialiser
	/// </summary>
	void Init() override
	{
		m_weapon = &m_entity->getComponent<WeaponComponent>();
		m_stats = &m_entity->getComponent<StatComponent>();

		// Health Bar
		HealthBar->m_current = m_stats->getHealth();
	}

	/// <summary>
	/// override update function
	/// </summary>
	void Update() override
	{
		// Health bar update
		if (HealthBar->m_current != m_stats->getHealth())
		{
			HealthBar->m_scale = m_stats->getHealth() / m_stats->getMaxHealth();
			HealthBar->m_width = HealthBar->m_maxwidth * HealthBar->m_scale;
			HealthBar->m_dst.w = HealthBar->m_width;
			HealthBar->m_current = m_stats->getHealth();
		}
	}

	/// <summary>
	/// Override function for draw method belonging to component 
	/// parent class
	/// </summary>
	void Draw() override
	{
		RenderSystem::Draw(m_texture, m_src, m_dst);
		RenderSystem::Draw(HealthBar->m_texture, HealthBar->m_src, HealthBar->m_dst);
	}
};