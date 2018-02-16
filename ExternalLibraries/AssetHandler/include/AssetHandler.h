#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>
#include <string>

using namespace std;

/// <summary>
/// This library works as storage for
/// .wav, .png and .ttf files. It uses
/// a map structer for storage and the
/// identifying value is a string so
/// music, fonts and images are easily
/// accessible through using tags.
/// </summary>
/// <author>Jack Keogh</author>

class AssetHandler
{
private:
	static AssetHandler * m_instance;
	map<string, SDL_Texture*> Textures;
	map<string, Mix_Chunk*> Sounds;
	map<string, TTF_Font*> Fonts;

	AssetHandler()
	{
		Textures = map<string, SDL_Texture*>();
		Sounds = map<string, Mix_Chunk*>();
		Fonts = map<string, TTF_Font*>();
	}

public:
	static AssetHandler * Instance()
	{
		if (!m_instance)
		{
			m_instance = new AssetHandler();
		}

		return m_instance;
	}

	/// <summary>
	/// Loads in a texture and adds it to the texture storage.
	/// </summary>
	/// <param name="Tag">string which will be used as an ID value.</param>
	/// <param name="Path">string to define the location of the texture.</param>
	/// <param name="Renderer">SDL_Renderer ptr to use to load an IMG.</param>
	void addTexture(string Tag, string Path, SDL_Renderer * Renderer);

	/// <summary>
	/// Loads in a sound and adds it to the sound storage.
	/// </summary>
	/// <param name="Tag">string which will be used as an ID value.</param>
	/// <param name="Path">string to define file location of the sound.</param>
	void addSound(string Tag, string Path);

	/// <summary>
	/// Loads in a font and adds it to the font storage.
	/// </summary>
	/// <param name="Tag">string which will be used as an ID value.</param>
	/// <param name="Path">string to define file location of the font.</param>
	/// <param name="size">int defining the size of the font.</param>
	void addFont(string Tag, string Path, int size);

	/// <summary>
	/// Gets a texture from the texture storage.
	/// </summary>
	/// <param name="Tag">string ID</param>
	/// <returns>An SDL_Texture.</returns>
	SDL_Texture * getTexture(string Tag);

	/// <summary>
	/// Gets a Mix_Chunk from the sound storage.
	/// </summary>
	/// <param name="Tag">string ID</param>
	/// <returns>A Mix_Chunk.</returns>
	Mix_Chunk * getSound(string Tag);

	/// <summary>
	/// Gets a TTF_Font from the font storage.
	/// </summary>
	/// <param name="Tag">string ID</param>
	/// <returns>A TTF_Font.</returns>
	TTF_Font * getFont(string Tag);
};