#include "Text.h"

Text::Text(string output, SDL_Rect rect, SDL_Color colour, string font)
{
	m_output = output;
	m_position = rect;
	m_colour = colour;
	m_font = font;
	m_asset = AssetHandler::Instance();

	SDL_Surface * m_surface = TTF_RenderText_Solid(m_asset->getFont(m_font), m_output.c_str(), m_colour);
	m_text = SDL_CreateTextureFromSurface(RenderSystem::Renderer(), m_surface);

	SDL_FreeSurface(m_surface);

	m_position.w = m_surface->w;
	m_position.h = m_surface->h;
}

Text::~Text()
{
}

void Text::setRect(SDL_Rect rect)
{
	m_position = rect;
}

void Text::setRect(float x, float y, float w, float h)
{
	m_position.x = x;
	m_position.y = y;
	m_position.w = w;
	m_position.h = h;
}

void Text::setPosition(SDL_Rect pos)
{
	m_position.x = pos.x;
	m_position.y = pos.y;
}

void Text::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void Text::setSize(SDL_Rect size)
{
	m_position.w = size.w;
	m_position.h = size.h;
}

void Text::setSize(float w, float h)
{
	m_position.w = w;
	m_position.h = h;
}

void Text::setText(string output)
{
	m_output = output;

	SDL_DestroyTexture(m_text);

	SDL_Surface * m_surface = TTF_RenderText_Solid(m_asset->getFont(m_font), m_output.c_str(), m_colour);
	m_text = SDL_CreateTextureFromSurface(RenderSystem::Renderer(), m_surface);

	SDL_FreeSurface(m_surface);

	m_position.w = m_surface->w;
	m_position.h = m_surface->h;
}

void Text::Draw()
{
	RenderSystem::Draw(m_text, m_position);
}
