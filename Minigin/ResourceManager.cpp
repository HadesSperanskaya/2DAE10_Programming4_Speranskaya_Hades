#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Font.h"

using namespace Engine;

ResourceManager::ResourceManager(const std::string& dataPath, SDL_Renderer* sdlRenderer) :
	m_DataPath(dataPath),
	m_SDLRenderer(sdlRenderer)
{
	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

ResourceManager::~ResourceManager()
{
	m_FontResourcePointers.clear();
	m_Texture2DResourcePointers.clear();
}

Texture2D* ResourceManager::LoadTexture(const std::string& file)
{
	m_Texture2DResourcePointers.push_back(std::unique_ptr<Texture2D>(new Texture2D(m_DataPath + file)));
	return m_Texture2DResourcePointers.back().get();
}

Font* ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	m_FontResourcePointers.push_back(std::unique_ptr<Font>(new Font(m_DataPath + file, size)));
	return m_FontResourcePointers.back().get();
}

Texture2D* ResourceManager::CreateTexture2DFromText(const SDL_Color color, Font* font, const std::string& text)
{
	m_Texture2DResourcePointers.push_back(std::unique_ptr<Texture2D>(new Texture2D(color, font, text)));
	return m_Texture2DResourcePointers.back().get();
}

SDL_Texture* ResourceManager::CreateSDLTextureFromText(const SDL_Color color, Font* font, const std::string& text)
{
	if (text.size() <= 0)
	{
		return nullptr;
	}

	const auto surf = TTF_RenderText_Blended(font->GetFont(), text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}

	auto texture = SDL_CreateTextureFromSurface(m_SDLRenderer, surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}

	SDL_FreeSurface(surf);

	return texture;
}
