#include <glm/vec2.hpp>
#include <string>


#ifndef TEXTURE2D_HEADER
#define TEXTURE2D_HEADER

struct SDL_Texture;

namespace Engine
{
	class Font;


	class Texture2D final
	{
	public:
		//functions
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

		SDL_Texture* GetSDLTexture() const;
		glm::ivec2 GetSize() const;

		void ReplaceSDLTexture(SDL_Texture* texture);

	private:

		//functions
		//explicitly deleted
		Texture2D() = delete;

		//elements
		SDL_Texture* m_Texture{ nullptr };
	};
}

#endif