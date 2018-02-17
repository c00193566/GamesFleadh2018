#pragma once
#include <SDL.h>
#include <iostream>
#include <AssetHandler.h>
#include "Components.h"
#include "Factory.h"

/// <class>InputSystem</class>
/// <summary>
/// This class will handle key inputs and
/// call the relevant command.
/// </summary>
/// <author>Jack Keogh</author>

using namespace std;

class InputSystem
{
private:
	bool up;
	bool down;
	bool left; 
	bool right;
	bool fire;
	int MouseX;
	int MouseY;
	AssetHandler * m_asset;

public:
	InputSystem();

	/// <summary>
	/// Checks key down event and if the key pressed corresponds
	/// to a keycode belonging to a player entity.
	/// </summary>
	/// <param name="e">SDL_event</param>
	/// <param name="entity">vector of unique ptr of Entity to loop through entities until
	/// player is found.</param>
	void KeyPressed(SDL_Event e, vector<Entity*> &entity);

	/// <summary>
	/// Checks key up event and if the key up corresponds
	/// to a keycode belonging to a player entity.
	/// </summary>
	/// <param name="e">SDL_event</param>
	/// <param name="entity">vector of unique ptr of Entity to loop through entities until
	/// player is found.</param>
	void KeyReleased(SDL_Event e, vector<Entity*> &entity);

	/// <summary>
	/// Checks if the left mouse button is pressed or released.
	/// </summary>
	/// <param name="e">SDL_event</param>
	void MouseButton(SDL_Event e);

	/// <summary>
	/// Checks mouse movement and updates the player entities rotation.
	/// </summary>
	/// <param name="e">SDL_event</param>
	void MouseMove(SDL_Event e);

	/// <summary>
	/// Updates the player based on current keys pressed and released.
	/// </summary>
	/// <param name="entity">vector of unique ptr of Entity to loop through entities until
	/// player is found.</param>
	void Update(EntityManager * Manager, vector<Entity*> &entity, PlayerBulletFactory * BulletFactory);
};