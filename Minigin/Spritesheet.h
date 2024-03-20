#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <memory>


#ifndef SPRITESHEET_HEADER
#define SPRITESHEET_HEADER

struct SDL_Texture;

namespace Engine
{
	class Font;


	struct SpritesheetInformation
	{
		const int rows;
		const int columns;
		const int animations;
		const int singleCellPixelWidth;
		const int singleCellPixelHeight;

	};

	struct AnimationInformation
	{
		const int startRow;
		const int startColumn;
		const int frames;
		const std::string animationName;

	};


	class Spritesheet final
	{
	public:
		//functions
		explicit Spritesheet(SDL_Texture* texture, const SpritesheetInformation& spritesheetInformation);
		~Spritesheet();

		Spritesheet(const Spritesheet&) = delete;
		Spritesheet(Spritesheet&&) = delete;
		Spritesheet& operator= (const Spritesheet&) = delete;
		Spritesheet& operator= (const Spritesheet&&) = delete;


		void AddAnimationInformation(const AnimationInformation& information);

		SDL_Texture* GetSDLTexture() const;
		int GetWidth() const;
		int GetHeight() const;

		const AnimationInformation* const GetAnimationInformation(int animationIndex) const;

	private:

		//functions
		//explicitly deleted
		Spritesheet() = delete;

		//elements
		SDL_Texture* m_TexturePointer{ nullptr };

		SpritesheetInformation m_SpritesheetInformation;

		std::vector<std::unique_ptr<AnimationInformation>> m_AnimationsDetails;



	};
}

#endif