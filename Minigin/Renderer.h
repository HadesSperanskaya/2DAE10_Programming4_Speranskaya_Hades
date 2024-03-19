#include <SDL.h>

#ifndef RENDERER_HEADER
#define RENDERER_HEADER

namespace Engine
{
	class Scene;
	class Texture2D;

	class Renderer final
	{
		
	public:
		//functions
		Renderer(SDL_Window* window);
		~Renderer();

		Renderer(const Renderer& other) = delete;
		Renderer(Renderer&& other) = delete;
		Renderer& operator=(const Renderer& other) = delete;
		Renderer& operator=(Renderer&& other) = delete;

		void Render(Scene* scene);

		static void RenderTexture(Texture2D* texture, float x, float y);
		static void RenderTexture(Texture2D* texture, float x, float y, float width, float height);


		//elements
		SDL_Color m_BackgroundColor{};
		static SDL_Renderer* m_SDLRenderer;


	private:
		//functions
		//default construct explicitly deleted.
		Renderer() = delete;

		//elements
		SDL_Window* m_Window{nullptr};
	};
}

#endif