#include <SDL.h>
#include "InputManager.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
//#include <WinBase.h>

bool Engine::InputManager::ProcessInput()
{
	//ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	//XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}
