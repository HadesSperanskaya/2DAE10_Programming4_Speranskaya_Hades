#pragma once
#include <SDL.h>

namespace Engine
{
	class Scene;

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

	
		SDL_Renderer* GetSDLRenderer() const;

		//elements
		SDL_Color m_BackgroundColor{};

	private:

		//elements
		SDL_Renderer* m_SDLRenderer;
		SDL_Window* m_Window{};
	};
}

