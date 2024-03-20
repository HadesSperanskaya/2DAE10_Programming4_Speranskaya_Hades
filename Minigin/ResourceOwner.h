#include <string>
#include <memory>
#include <vector>
#include <SDL.h>


#ifndef RESOURCE_OWNER_HEADER
#define RESOURCE_OWNER_HEADER


namespace Engine
{
	class Texture2D;
	class Spritesheet;
	class Font;

	struct SpritesheetInformation;

	class ResourceOwner final
	{
	public:
		//functions
		ResourceOwner(const std::string& dataPath);
		~ResourceOwner() = default;		
		
		ResourceOwner(const ResourceOwner& other) = delete;
		ResourceOwner(ResourceOwner&& other) = delete;
		ResourceOwner& operator=(const ResourceOwner& other) = delete;
		ResourceOwner& operator=(ResourceOwner&& other) = delete;


		static Texture2D* LoadTexture(const std::string& file);
		static Font* LoadFont(const std::string& file, unsigned int size);
		static Spritesheet* LoadSpritesheet(const std::string& file, const SpritesheetInformation& spritesheetInformation);

		static Texture2D* CreateTexture2DFromText(const SDL_Color color, Font* font, const std::string& text);
		static SDL_Texture* CreateSDLTextureFromText(const SDL_Color color, Font* font, const std::string& text);





	private:
		//functions
		//explicitly deleted default constructor
		ResourceOwner() = delete;

		//elements
		static std::string m_DataPath;

		static std::vector<std::unique_ptr<Texture2D>> m_Texture2DResourcePointers;
		static std::vector<std::unique_ptr<Spritesheet>> m_SpritesheetResourcePointers;
		static std::vector<std::unique_ptr<Font>> m_FontResourcePointers;



	};
}
#endif