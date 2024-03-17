#pragma once
#include <glm/vec2.hpp>
#include <string>
#include <SDL.h>


namespace Engine
{
	class Font;

	class Texture2D final
	{
	public:
		Texture2D(SDL_Texture* texture);
		~Texture2D();

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

		SDL_Texture* GetSDLTexture() const;
		glm::ivec2 GetSize() const;


		void ReplaceSDLTexture(SDL_Texture* texture);

	private:

		SDL_Texture* m_Texture{ nullptr };
	};
}
