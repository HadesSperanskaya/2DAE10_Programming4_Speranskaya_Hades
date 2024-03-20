#include "Spritesheet.h"
#include <SDL.h>

using namespace Engine;


Spritesheet::Spritesheet(SDL_Texture* texture, const SpritesheetInformation& spritesheetInformation):
	m_TexturePointer{texture},
	m_SpritesheetInformation{spritesheetInformation}
{
}

Spritesheet::~Spritesheet()
{
	SDL_DestroyTexture(m_TexturePointer);
}

void Spritesheet::AddAnimationInformation(const AnimationInformation& information)
{
	m_AnimationsDetails.push_back(std::make_unique<AnimationInformation>(information));
}


int Spritesheet::GetWidth() const
{
	return m_SpritesheetInformation.singleCellPixelWidth;
}

int Spritesheet::GetHeight() const
{
	return m_SpritesheetInformation.singleCellPixelHeight;
}

const AnimationInformation* const  Spritesheet::GetAnimationInformation(int animationIndex) const
{
	return m_AnimationsDetails[animationIndex].get();
}


SDL_Texture* Spritesheet::GetSDLTexture() const
{
	return m_TexturePointer;
}

