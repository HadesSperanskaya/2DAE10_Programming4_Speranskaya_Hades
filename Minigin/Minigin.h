#pragma once
#include <string>
#include <functional>
#include <memory>


#ifndef ENGINE_HEADER
#define ENGINE_HEADER
struct SDL_Window;

namespace Engine
{
	class Renderer;
	class Scene;
	class ResourceOwner;
	class InputHandler;


	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void(Minigin* engine)>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;


		static std::unique_ptr<Scene> m_ScenePointer;
		static std::unique_ptr<InputHandler> m_InputHandlerPointer;

	private:
		
		std::unique_ptr<Renderer> m_RendererPointer;
		std::unique_ptr<ResourceOwner> m_ResourceOwnerPointer;

		SDL_Window* m_WindowPointer;

	};
}

#endif