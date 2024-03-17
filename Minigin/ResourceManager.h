#pragma once
#include <string>
#include <memory>
#include <vector>
#include <SDL.h>

namespace Engine
{
	class Texture2D;
	class Font;


	class ResourceManager final
	{
	public:
		//functions
		ResourceManager(const std::string& data, SDL_Renderer* sdlRenderer);
		~ResourceManager();
		ResourceManager(const ResourceManager& other) = delete;
		ResourceManager(ResourceManager&& other) = delete;
		ResourceManager& operator=(const ResourceManager& other) = delete;
		ResourceManager& operator=(ResourceManager&& other) = delete;



		Texture2D* LoadTexture(const std::string& file);
		Font* LoadFont(const std::string& file, unsigned int size);
		Texture2D* CreateTexture2DFromText(const SDL_Color color, Font* font, const std::string & text);
		SDL_Texture* CreateSDLTextureFromText(const SDL_Color color, Font* font, const std::string& text);



	private:
		//elements
		std::string m_DataPath;
		SDL_Renderer* m_SDLRenderer;

		std::vector<std::unique_ptr<Texture2D>> m_Texture2DResourcePointers;
		std::vector<std::unique_ptr<Font>> m_FontResourcePointers;

	};
}
