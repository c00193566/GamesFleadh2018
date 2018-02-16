#pragma once
#include <iostream>
#include <SDL_image.h>
#include "RenderSystem.h"
#include "TransformComponent.h"

using namespace std;

/// <class>SpriteComponent</class>
/// <summary>
/// This class uses a reference to 
/// the transform component to draw
/// an sdl_texture at a particular 
/// position.
/// </summary>
/// <author>Jack Keogh</author>

class SpriteComponent : public Component
{
private:
	TransformComponent * m_transform;
	SDL_Rect m_dstRect;
	SDL_Rect m_srcRect;
	SDL_Texture * m_texture;
	float rotation;

public:
	/// <summary>
	/// Overload constructor that defaults values to 0.
	/// </summary>
	/// <param name="path">const char ptr defining path to texture.</param>
	/// <param name="w">int to define src rect width.</param>
	/// <param name="h">int to define src rect height.</param>
	SpriteComponent(const char* path = "", int w = 0, int h = 0)
	{
		if (!(m_texture = IMG_LoadTexture(RenderSystem::Renderer(), path)))
		{
			cout << IMG_GetError << endl;
		}

		m_srcRect.w = w;
		m_srcRect.h = h;
	}

	/// <summary>
	/// Overload constructor that defaults values to 0.
	/// </summary>
	/// <param name="Texture">SDL_Texture ptr defining the texture.</param>
	/// <param name="w">int to define src rect width.</param>
	/// <param name="h">int to define src rect height.</param>
	SpriteComponent(SDL_Texture * Texture, int w = 0, int h = 0)
	{
		m_texture = Texture;

		m_srcRect.w = w;
		m_srcRect.h = h;
	}

	void Init() override
	{
		m_transform = &m_entity->getComponent<TransformComponent>();

		m_dstRect.x = m_transform->position.x;
		m_dstRect.y = m_transform->position.y;
		m_dstRect.w = m_transform->width;
		m_dstRect.h = m_transform->height;
		rotation = m_transform->rotation;
	}

	void Update() override
	{
		m_dstRect.x = m_transform->position.x;
		m_dstRect.y = m_transform->position.y;
		m_dstRect.w = m_transform->width * m_transform->scale;
		m_dstRect.h = m_transform->height * m_transform->scale;
		rotation = m_transform->rotation;
	}

	void Draw()
	{
		RenderSystem::Draw(m_texture, m_srcRect, m_dstRect, rotation);
	}
};