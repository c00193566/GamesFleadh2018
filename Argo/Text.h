#pragma once
#include <AssetHandler.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "RenderSystem.h"

/// <class>Text</class>
/// <summary>
/// This class will convert a string into a drawable
/// sdl_texture and be able to render it to the screen.
/// </summary>
/// <author>Jack Keogh</author>

using namespace std;

class Text
{
private:
	string m_output;
	string m_font;
	SDL_Texture * m_text;
	SDL_Color m_colour;
	SDL_Rect m_position;
	AssetHandler * m_asset;

public:
	/// <summary>
	/// Default constructor with overload parameters availables
	/// </summary>
	Text(string output = "", SDL_Rect rect = { 0,0,0,0 }, SDL_Color colour = { 255,255,255,255 }, string font = "Arial");

	/// <summary>
	/// Default deconstructor
	/// </summary>
	~Text();

	// Set Rectangle
	void setRect(SDL_Rect rect);
	void setRect(float x, float y, float w, float h);

	// Set Position
	void setPosition(SDL_Rect pos);
	void setPosition(float x, float y);

	// Set size
	void setSize(SDL_Rect size);
	void setSize(float w, float h);

	// Set Text
	void setText(string output);

	// Draw text
	void Draw();
};