#include <stdexcept>

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Minigin.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

using namespace Engine;


Texture2D::Texture2D(const std::string& fullPath) 
{
	m_Texture = IMG_LoadTexture(Minigin::m_RendererPointer->GetSDLRenderer(), fullPath.c_str());

	if (m_Texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
}

Texture2D::Texture2D(const SDL_Color color, Font* font, const std::string& text)
{
	if (text.empty())
	{
		m_Texture = nullptr;
		return;
	}


	const auto surf = TTF_RenderText_Blended(font->GetFont(), text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}

	m_Texture = SDL_CreateTextureFromSurface(Minigin::m_RendererPointer->GetSDLRenderer(), surf);
	if (m_Texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}

	SDL_FreeSurface(surf);
}

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

glm::ivec2 Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* Texture2D::GetSDLTexture() const
{
	return m_Texture;
}


void Texture2D::RenderTexture(const float x, const float y) const
{
	if (m_Texture == nullptr)
	{
		return;
	}

	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(Minigin::m_RendererPointer->GetSDLRenderer(), m_Texture, nullptr, &dst);
}

void Texture2D::RenderTexture(const float x, const float y, const float width, const float height) const
{
	if (m_Texture == nullptr)
	{
		return;
	}

	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	SDL_RenderCopy(Minigin::m_RendererPointer->GetSDLRenderer(), m_Texture, nullptr, &dst);
}

void Texture2D::ReplaceSDLTexture(SDL_Texture* texture)
{
	SDL_DestroyTexture(m_Texture);
	m_Texture = texture;
}