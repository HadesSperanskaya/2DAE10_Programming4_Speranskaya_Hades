#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "ResourceOwner.h"
#include "Renderer.h"

using namespace Engine;

std::vector<std::unique_ptr<Texture2D>> ResourceOwner::m_Texture2DResourcePointers;
std::vector<std::unique_ptr<Font>> ResourceOwner::m_FontResourcePointers;
std::string m_DataPath;

ResourceOwner::ResourceOwner(const std::string& dataPath)
{
	m_DataPath = dataPath;
	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

Texture2D* ResourceOwner::LoadTexture(const std::string& file)
{
	m_Texture2DResourcePointers.push_back(std::unique_ptr<Texture2D>(new Texture2D(IMG_LoadTexture(Renderer::m_SDLRenderer, (m_DataPath + file).c_str()))));
	return m_Texture2DResourcePointers.back().get();
}

Font* ResourceOwner::LoadFont(const std::string& file, unsigned int size)
{
	m_FontResourcePointers.push_back(std::unique_ptr<Font>(new Font(m_DataPath + file, size)));
	return m_FontResourcePointers.back().get();
}

Texture2D* ResourceOwner::CreateTexture2DFromText(const SDL_Color color, Font* font, const std::string& text)
{
	m_Texture2DResourcePointers.push_back(std::unique_ptr<Texture2D>(new Texture2D(CreateSDLTextureFromText(color, font, text))));
	return m_Texture2DResourcePointers.back().get();
}

SDL_Texture* ResourceOwner::CreateSDLTextureFromText(const SDL_Color color, Font* font, const std::string& text)
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

	auto texture = SDL_CreateTextureFromSurface(Renderer::m_SDLRenderer, surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}

	SDL_FreeSurface(surf);

	return texture;
}

