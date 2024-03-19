#pragma warning( push, 3 )
#include <SDL.h>
#include <Windows.h>
#include <Xinput.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#pragma warning( pop )


#include "GameObject.h"
#include "InputHandler.h"

#include "CommandsSetPlayer.h"


#pragma region Structs

namespace Engine
{
	enum struct ControllerButton
	{
		DpadUp = 0x0001,
		DpadDown = 0x0002,
		DpadLeft = 0x0004,
		DpadRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		//Left_Thumb = 0x0040,
		//Right_Thumb = 0x0080,
		//Left_Shoulder = 0x0100,
		//Right_Shoulder = 0x0200,
		A = 0x1000,
		B = 0x2000,
		X = 0x4000,
		Y = 0x8000
	};

	enum struct TriggerState
	{
		IsDown = 0,
		IsUp = 1,
		WasPressed = 2,
		WasReleased = 3
	};

	struct TriggerButton
	{
		ControllerButton button;
		TriggerState trigger;

		bool operator<(const TriggerButton& rhs) const
		{
			if (this->button < rhs.button)
			{
				return true;
			}
			else if (this->button > rhs.button)
			{
				return false;
			}
			else
			{
				if (this->trigger < rhs.trigger)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};

	};

	struct XinputController
	{
		bool exists{ false };
		XINPUT_STATE state{};
		GameObject* controlledActor{ nullptr };
	};

	struct TriggerKey
	{
		SDL_KeyCode key;
		TriggerState trigger;

		bool operator<(const TriggerKey& rhs) const
		{
			if (this->key < rhs.key)
			{
				return true;
			}
			else if (this->key > rhs.key)
			{
				return false;
			}
			else
			{
				if (this->trigger < rhs.trigger)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};
	};

	struct Keyboard
	{
		bool exists{ false };
		GameObject* controlledActor{ nullptr };
	};


}

#pragma endregion Structs


//XINPUT INPUT HANDLER
class Engine::InputHandler::XinputInputHandlerImpl
{

public:
	//functions

	void Initialise()
	{
		for (int i{}; i < int(XUSER_MAX_COUNT); ++i)
		{
			m_XinputControllers.push_back(XinputController{});
		}

		m_XinputControllerCommands.emplace(std::make_pair<TriggerButton, std::unique_ptr<Command>>(TriggerButton{ ControllerButton::DpadDown, TriggerState::IsDown }, std::unique_ptr<Command>(new MoveCommand())));

	}

	void CheckForNewXinputControllers()
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
			if (dwordResult == ERROR_SUCCESS && m_XinputControllers[int(i)].exists == false)
			{
				// Controller is connected. mark as existing, and overwrite whatever state it had stored
				m_XinputControllers[int(i)].exists = true;
				m_XinputControllers[int(i)].state = state;
			}
			//if a controller is not found, 
			else
			{
				// Controller is not connected. set connected bool as false. do not store state
				m_XinputControllers[int(i)].exists = false;
			}
		}
	}

	void HandleXinput()
	{
		DWORD dwordResult;
		//go over all controllers
		//controllers are indexed 0 to 3, based on which port they connect to
		//that is not changeable, so if there is only one controller,
		//it will not automatically be at index 0. so go over all indexes


		for (DWORD i{ 0 }; i < XUSER_MAX_COUNT; ++i)
		{
			//only handle input for controllers marked as true, and which have actors they control
			if (m_XinputControllers[int(i)].exists && m_XinputControllers[int(i)].controlledActor != nullptr)
			{

				XINPUT_STATE currentState;
				ZeroMemory(&currentState, sizeof(XINPUT_STATE));
				dwordResult = XInputGetState(i, &currentState);

				if (dwordResult == ERROR_SUCCESS)
				{
					// Controller is connected. Process input.

					//check for changes in packet number to find if anythinng happened

					if (currentState.dwPacketNumber != m_XinputControllers[int(i)].state.dwPacketNumber)
					{
						//check gamepad to get more detailed state information
						auto buttonChanges = currentState.Gamepad.wButtons ^ m_XinputControllers[int(i)].state.Gamepad.wButtons;
						WORD buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
						WORD buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);

						//go over each command to see if it is called?

						for (auto& command : m_XinputControllerCommands)
						{
							switch (command.first.trigger)
							{
							case TriggerState::IsDown:
								if (IsPressed(currentState.Gamepad.wButtons, int(command.first.button)))
								{
									command.second->Execute(*m_XinputControllers[int(i)].controlledActor);
								}
								break;

							case TriggerState::WasPressed:

								if (IsDownThisFrame(buttonsPressedThisFrame, int(command.first.button)))
								{
									command.second->Execute(*m_XinputControllers[int(i)].controlledActor);
								}
								break;


							case TriggerState::WasReleased:

								if (IsUpThisFrame(buttonsReleasedThisFrame, int(command.first.button)))
								{
									command.second->Execute(*m_XinputControllers[int(i)].controlledActor);
								}

								break;

							default:

								break;
							}
						}

					}

				}

				else
				{
					//Controller was disconnected since last check, set controller as non-existant
					m_XinputControllers[int(i)].exists = false;

				}
			}
		}

	}
	
	void AssignActorToXinputController(int controllerIndex, GameObject* actor)
	{
		m_XinputControllers[controllerIndex].controlledActor = actor;
	};

	void AssignActorToAllXinputControllers(GameObject* actor)
	{
		for (XinputController& controller : m_XinputControllers)
		{
			controller.controlledActor = actor;
		}
	};

	void AssignActorToFirstFreeXinputController(GameObject* actor)
	{
		for (XinputController& controller : m_XinputControllers)
		{
			if (controller.controlledActor == nullptr)
			{
				controller.controlledActor = actor;
				//since a free controller was found, it is time to return
				return;
			}
		}
	};

	//elements


private:

	//functions
	bool IsDownThisFrame(WORD buttonsPressedThisFrame, unsigned int button) const
	{
		return buttonsPressedThisFrame & button;
	}

	bool IsUpThisFrame(WORD buttonsReleasedThisFrame, unsigned int button) const
	{
		return buttonsReleasedThisFrame & button;
	}

	bool IsPressed(WORD stateOfButtons, unsigned int button) const
	{
		return stateOfButtons & button;
	}

	//elements


	std::vector<XinputController> m_XinputControllers{};
	std::map<TriggerButton, std::unique_ptr<Command>> m_XinputControllerCommands{};

};


//KEYBOARD INPUT HANDLER 
class Engine::InputHandler::KeyboardInputHandlerImpl
{
public:
	//functions
	void Initialise()
	{
		//for now only deal with one keyboard, but could theoretically expand to deal with more
		m_Keyboards.push_back(Keyboard{});

		m_KeyboardCommands.emplace(std::make_pair<TriggerKey, std::unique_ptr<Command>>(TriggerKey{ SDLK_w, TriggerState::IsDown }, std::unique_ptr<Command>(new MoveCommand)));


	}

	bool HandleKeyboardInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				return false;
			}

			if (e.type == SDL_PRESSED)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_w:
					break;

				case SDLK_a:
					break;

				case SDLK_s:
					break;

				case SDLK_d:
					break;
				}
			}

			//process event for IMGUI
			ImGui_ImplSDL2_ProcessEvent(&e);


		}

		return true;
	}

	void AssignActorToKeyboard(int keyboard, GameObject* actor)
	{
		m_Keyboards[keyboard].controlledActor = actor;
	};

	//elements


private:

	//elements

	std::vector<Keyboard> m_Keyboards{};
	std::map<TriggerKey, std::unique_ptr<Command>> m_KeyboardCommands{};
};



using namespace Engine;


// INPUT HANDLER FUNCTION IMPLEMENTATIONS

InputHandler::InputHandler() :
	m_XinputImplPointer{std::make_unique<XinputInputHandlerImpl>()},
	m_KeyboardImplPointer{ std::make_unique<KeyboardInputHandlerImpl>() }
{
	m_XinputImplPointer->Initialise();
	m_KeyboardImplPointer->Initialise();
}


bool InputHandler::ProcessInput()
{
	m_XinputImplPointer->HandleXinput();

	if (m_KeyboardImplPointer->HandleKeyboardInput() != true)
	{
		return false;
	}

	return true;
}

void InputHandler::AssignActorToXinputController(int controllerIndex, GameObject* actor)
{
	m_XinputImplPointer->AssignActorToXinputController(controllerIndex, actor);
};

void InputHandler::AssignActorToAllXinputControllers(GameObject* actor)
{
	m_XinputImplPointer->AssignActorToAllXinputControllers(actor);

};

void InputHandler::AssignActorToFirstFreeXinputController(GameObject* actor)
{
	m_XinputImplPointer->AssignActorToFirstFreeXinputController(actor);

};

void InputHandler::AssignActorToKeyboard(int keyboard, GameObject* actor)
{
	m_KeyboardImplPointer->AssignActorToKeyboard(keyboard, actor);
};


