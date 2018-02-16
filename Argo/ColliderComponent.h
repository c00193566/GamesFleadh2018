#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

/// <class>ColliderComponent</class>
/// <summary>
/// This component will be used to keep track
/// of 5 SDL_Rectangle which will act as colliders
/// for an entity. A central collider, a collider
/// with an offset to the left, right, top and bottom.
/// </summary>
/// <author>Jack Keogh</author>

class ColliderComponent : public Component
{
private:
	TransformComponent * m_transform;
	SDL_Rect m_central;
	SDL_Rect m_left;
	SDL_Rect m_right;
	SDL_Rect m_top;
	SDL_Rect m_bottom;

public:
	/// <summary>
	/// Default constructor for Collider Component.
	/// </summary>
	ColliderComponent() {};

	/// <summary>
	/// Default destructor for Collider Component.
	/// </summary>
	~ColliderComponent() {};

	/// <summary>
	/// Override initialiser for Collider Component.
	/// </summary>
	void Init() override;

	/// <summary>
	/// Override update for Collider Component.
	/// </summary>
	void Update() override;

	/// <summary>
	/// Getter functions
	/// </summary>
	SDL_Rect getCollider() { return m_central; };
	SDL_Rect getTop() { return m_top; };
	SDL_Rect getBottom() { return m_bottom; };
	SDL_Rect getLeft() { return m_left; };
	SDL_Rect getRight() { return m_right; };
};