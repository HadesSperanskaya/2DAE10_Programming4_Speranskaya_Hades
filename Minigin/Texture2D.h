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
		Texture2D(const std::string& fullPath);
		Texture2D(const SDL_Color color, Font* font, const std::string& text);
		~Texture2D();

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

		SDL_Texture* GetSDLTexture() const;
		glm::ivec2 GetSize() const;

		void RenderTexture(float x, float y) const;
		void RenderTexture(float x, float y, float width, float height) const;

		void ReplaceSDLTexture(SDL_Texture* texture);

	private:

		SDL_Texture* m_Texture{ nullptr };
	};
}
