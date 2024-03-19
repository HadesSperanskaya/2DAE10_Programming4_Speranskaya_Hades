#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <chrono>
#include <thread>

#include <wingdi.h>

#include "Minigin.h"
#include "ResourceOwner.h"
#include "Renderer.h"

#include "InputHandler.h"
#include "Scene.h"





void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

using namespace Engine;

std::unique_ptr<Scene> Minigin::m_ScenePointer{ nullptr };
std::unique_ptr<InputHandler> Minigin::m_InputHandlerPointer{ nullptr };

Minigin::Minigin(const std::string &dataPath) : 
	m_WindowPointer(nullptr)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_WindowPointer = SDL_CreateWindow("Programming 4 assignment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640,480, SDL_WINDOW_OPENGL);

	if (m_WindowPointer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}


	m_RendererPointer = std::make_unique<Renderer>(m_WindowPointer);

	m_ResourceOwnerPointer = std::make_unique<ResourceOwner>(dataPath);

	m_ScenePointer = std::unique_ptr<Scene>(new Scene());

	m_InputHandlerPointer = std::unique_ptr<InputHandler>(new InputHandler());
}

Engine::Minigin::~Minigin()
{
	m_RendererPointer.reset();

	SDL_DestroyWindow(m_WindowPointer);
	SDL_Quit();
}

void Engine::Minigin::Run(const std::function<void(Minigin* engine)>& load)
{
	load(this);

	
	bool doContinue = true;

	//variable to store starting point before loop, and then last time point
	auto lastTime = std::chrono::high_resolution_clock::now();


	//fixed update functionatlity currenly commented out. may be relevant later for phyics, so not deleted.
	//float lag = 0.0f;
	//float fixedTimeStep{ 1 };


	const float millisecondsInSecond{ 1000.f };

#ifdef _WIN32 
	const long millisecondsPerFrame{ long(millisecondsInSecond / float(GetDeviceCaps(GetDC(NULL), VREFRESH))) };

#else
	const float desiredFPS{ 140 };

	const long millisecondsPerFrame{ long(millisecondsInSecond / desiredFPS) };

#endif

	while (doContinue)
	{
		//get and store current point in time
		const auto currentTime = std::chrono::high_resolution_clock::now();
		
		//get delta time from the difference between last stored timepoint and now
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

		//update last time to be the current time
		lastTime = currentTime;

		doContinue = m_InputHandlerPointer->ProcessInput();


		//fixed update functionatlity currenly commented out. may be relevant later for physics, so not deleted.
		//lag = lag + deltaTime;
		////for time dependent things (physics and networking), run through them as many times as it takes to catch up the present time
		//while(lag >= fixedTimeStep)
		//{
		//	sceneManager.FixedUpdate(fixedTimeStep);
		//	lag = lag - fixedTimeStep;
		//}



		m_ScenePointer->Update(deltaTime);
		m_RendererPointer->Render(m_ScenePointer.get());


		const auto sleepTime = currentTime + std::chrono::milliseconds(millisecondsPerFrame) - std::chrono::high_resolution_clock::now();

		std::this_thread::sleep_for(sleepTime);

	}
}
