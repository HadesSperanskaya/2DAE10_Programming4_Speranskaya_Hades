#include "Texture2D.h"

using namespace Engine;


Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
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

void Texture2D::ReplaceSDLTexture(SDL_Texture* texture)
{
	SDL_DestroyTexture(m_Texture);
	m_Texture = texture;
}