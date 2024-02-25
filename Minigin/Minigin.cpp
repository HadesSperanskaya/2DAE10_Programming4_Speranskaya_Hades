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
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

SDL_Window* g_window{};

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

dae::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	// todo: this update loop could use some work.
	bool doContinue = true;

	//variable to store starting point before loop, and then last time point
	auto lastTime = std::chrono::high_resolution_clock::now();

	float lag = 0.0f;

	const float millisecondsInSecond{ 1000.f };

#ifdef _WIN32 
	const long millisecondsPerFrame{ long(millisecondsInSecond / float(GetDeviceCaps(GetDC(NULL), VREFRESH))) };

#else
	const float desiredFPS{ 140 };

	const long millisecondsPerFrame{ long(millisecondsInSecond / desiredFPS) };

#endif
	float fixedTimeStep{ 1 };

	while (doContinue)
	{
		//get and store current point in time
		const auto currentTime = std::chrono::high_resolution_clock::now();
		
		//get delta time from the difference between last stored timepoint and now
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

		//update last time to be the current time

		lastTime = currentTime;
		lag = lag + deltaTime;

		doContinue = input.ProcessInput();


		//for time dependent things (physics and networking), run through them as many times as it takes
		//to catch up the present time
		while(lag >= fixedTimeStep)
		{
			sceneManager.FixedUpdate(fixedTimeStep);
			lag = lag - fixedTimeStep;
		}



		sceneManager.Update(deltaTime);
		renderer.Render();


		const auto sleepTime = currentTime + std::chrono::milliseconds(millisecondsPerFrame) - std::chrono::high_resolution_clock::now();


		std::this_thread::sleep_for(sleepTime);

	}
}
