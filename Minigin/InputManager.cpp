#pragma warning( push, 1 )
#include <SDL.h>
#include <Windows.h>
#pragma warning( pop )



#include "CommandsSetMovement.h"
#include "InputManager.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "GameObject.h"


using namespace Engine;
InputManager::InputManager()
{
	for (int i{}; i < int(XUSER_MAX_COUNT); ++i)
	{
		m_Controllers.push_back(Controller{});
	}
}

void InputManager::CheckForNewControllers()
{
	DWORD dwordResult;
	//go over all controllers
	//controllers are indexed 0 to 3, based on which port they connect to
	//that is not changeable, so if there is only one controller,
	//it will not automatically be at index 0. so go over all indexes


	for (DWORD i{ 0 }; i < XUSER_MAX_COUNT; ++i)
	{
		//variable to hold state
		XINPUT_STATE state;
		//
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		//set result to the input state of the controller
		dwordResult = XInputGetState(i, &state);

		//if a controller is found, and the controller is currently marked as not found
		if (dwordResult == ERROR_SUCCESS && m_Controllers[int(i)].exists == false)
		{
			// Controller is connected. mark as existing, and overwrite whatever state it had stored
			m_Controllers[int(i)].exists = true;
			m_Controllers[int(i)].state = state;
		}
		//if a controller is not found, 
		else
		{
			// Controller is not connected. set connected bool as false. do not store state
			m_Controllers[int(i)].exists = false;
		}
	}
}

bool InputManager::ProcessInput()
{
	DWORD dwordResult;
	//go over all controllers
	//controllers are indexed 0 to 3, based on which port they connect to
	//that is not changeable, so if there is only one controller,
	//it will not automatically be at index 0. so go over all indexes


	for (DWORD i{0}; i < XUSER_MAX_COUNT; ++i)
	{
		//only handle input for controllers marked as true, and which have actors they control
		if(m_Controllers[int(i)].exists && m_Controllers[int(i)].controlledActor != nullptr)
		{
			
			XINPUT_STATE currentState;
			ZeroMemory(&currentState, sizeof(XINPUT_STATE));
			dwordResult = XInputGetState(i, &currentState);

			if (dwordResult == ERROR_SUCCESS)
			{
				// Controller is connected. Process input.

				//check for changes in packet number to find if anythinng happened

				if (currentState.dwPacketNumber != m_Controllers[int(i)].state.dwPacketNumber)
				{
					//check gamepad to get more detailed state information



				}

			}

			else
			{
				//Controller was disconnected since last check, set controller as non-existant
				m_Controllers[int(i)].exists = false;

			}
		}
	}


	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}


void InputManager::AssignActorToAnyController(int controllerIndex, GameObject* actor)
{
	m_Controllers[controllerIndex].controlledActor = actor;
};

void InputManager::AssignActorToAllControllers(GameObject* actor)
{
	for (Controller& controller : m_Controllers)
	{
		controller.controlledActor = actor;
	}
};


void InputManager::AssignActorToFirstFreeController(GameObject* actor)
{
	for (Controller& controller : m_Controllers)
	{
		if (controller.controlledActor == nullptr)
		{
			controller.controlledActor = actor;
			//since a free controller was found, it is time to return
			return;
		}
	}
};



bool InputManager::IsDownThisFrame(WORD buttonsPressedThisFrame, unsigned int button) const
{
	return buttonsPressedThisFrame & button;
}

bool InputManager::IsUpThisFrame(WORD buttonsReleasedThisFrame, unsigned int button) const
{
	return buttonsReleasedThisFrame & button;
}

bool InputManager::IsPressed(WORD stateOfButtons, unsigned int button) const
{
	return stateOfButtons & button;
}



