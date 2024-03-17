#pragma once
#include <string>
#include <functional>
#include <memory>

struct SDL_Window;

namespace Engine
{
	class Renderer;
	class Scene;
	class ResourceManager;
	class InputManager;


	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;


		static std::unique_ptr<ResourceManager> m_ResourceManagerPointer;
		static std::unique_ptr<Renderer> m_RendererPointer;
		static std::unique_ptr<Scene> m_ScenePointer;
		static std::unique_ptr<InputManager> m_InputManagerPointer;


	private:

		SDL_Window* m_Window;

	};
}