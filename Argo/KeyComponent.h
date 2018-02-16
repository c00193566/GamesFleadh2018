#pragma once
#include <iostream>
#include <SDL.h>
#include "ECS.h"

/// <class>KeyComponent</class>
/// <summary>
/// This class will be used to bind
/// a users choice of keys to keycodes.
/// </summar>
/// <author>Jack Keogh</author>

class KeyComponent : public Component
{
private:
	SDL_Keycode m_right;
	SDL_Keycode m_left;
	SDL_Keycode m_up;
	SDL_Keycode m_down;

public:
	/// <summary>
	/// Default constructor that allows for overloaded values to be passed in.
	/// </summary>
	/// <param name="up">SDL_keycode for up button.</param>
	/// <param name="down">SDL_keycode for down button.</param>
	/// <param name="left">SDL_keycode for left button.</param>
	/// <param name="right">SDL_keycode for right button.</param>
	KeyComponent(SDL_Keycode up = SDLK_UP, SDL_Keycode down = SDLK_DOWN, SDL_Keycode left = SDLK_LEFT, SDL_Keycode right = SDLK_RIGHT) :
		m_right(right),
		m_left(left),
		m_up(up),
		m_down(down)
	{};

	SDL_Keycode Up() { return m_up; };
	SDL_Keycode Down() { return m_down; };
	SDL_Keycode Left() { return m_left; };
	SDL_Keycode Right() { return m_right; };
};