#pragma once
#include <string>
#include <memory>
#include <vector>
#include <SDL.h>

#include "Singleton.h"
#include "Texture2D.h"
#include "Font.h"

namespace Engine
{

	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		//functions
		void Initialise(const std::string& data, SDL_Renderer* sdlRenderer);
		~ResourceManager();


		Texture2D* LoadTexture(const std::string& file);
		Font* LoadFont(const std::string& file, unsigned int size);
		Texture2D* CreateTexture2DFromText(const SDL_Color color, Font* font, const std::string& text);
		SDL_Texture* CreateSDLTextureFromText(const SDL_Color color, Font* font, const std::string& text);



	private:
		//elements
		std::string m_DataPath;
		SDL_Renderer* m_SDLRenderer{ nullptr };

		std::vector<std::unique_ptr<Texture2D>> m_Texture2DResourcePointers;
		std::vector<std::unique_ptr<Font>> m_FontResourcePointers;

	};
}
