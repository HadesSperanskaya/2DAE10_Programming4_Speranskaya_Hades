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

	struct TriggerButton
	{
		XINPUT_CONTROLLER_BUTTON button;
		XINPUT_CONTROLLER_BUTTON_STATE trigger;

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
		unsigned int trigger{};

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
				return (this->trigger < rhs.trigger);

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
		CheckForNewXinputControllers();

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

			const int controllerIndexInVector = i;

			//if a controller is found, and the controller is currently marked as not found
			if (dwordResult == ERROR_SUCCESS && m_XinputControllers[controllerIndexInVector].exists == false)
			{
				// Controller is connected. mark as existing, and overwrite whatever state it had stored
				m_XinputControllers[controllerIndexInVector].exists = true;
				m_XinputControllers[controllerIndexInVector].state = state;
			}
			//if a controller is not found, 
			else
			{
				// Controller is not connected. set connected bool as false. do not store state
				m_XinputControllers[controllerIndexInVector].exists = false;
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

		int dwordIndex = 0;

		for (auto& controller : m_XinputControllers)
		{

			//only handle input for controllers marked as true, and which have actors they control
			if (controller.exists && controller.controlledActor != nullptr)
			{

				XINPUT_STATE currentState;
				ZeroMemory(&currentState, sizeof(XINPUT_STATE));
				dwordResult = XInputGetState(dwordIndex, &currentState);

				if (dwordResult == ERROR_SUCCESS)
				{
					// Controller is connected. Process input.

					//check for changes in packet number to find if anything happened
					

					if (currentState.dwPacketNumber != controller.state.dwPacketNumber)
					{
						//check gamepad to get more detailed state information
						auto buttonChanges = currentState.Gamepad.wButtons ^ controller.state.Gamepad.wButtons;
						WORD buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
						WORD buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);

						//go over each command to see if it is called?

						for (auto& command : m_XinputControllerCommands)
						{
							switch (command.first.trigger)
							{

							case XINPUT_CONTROLLER_BUTTON_STATE::IsDown:
								if (IsPressed(currentState.Gamepad.wButtons, unsigned int(command.first.button)))
								{
									command.second->Execute(*controller.controlledActor);
									
								}
								break;

							case XINPUT_CONTROLLER_BUTTON_STATE::WasPressed:

								if (IsDownThisFrame(buttonsPressedThisFrame, unsigned int(command.first.button)))
								{
									command.second->Execute(*controller.controlledActor);
									
								}
								break;


							case XINPUT_CONTROLLER_BUTTON_STATE::WasReleased:

								if (IsUpThisFrame(buttonsReleasedThisFrame, unsigned int(command.first.button)))
								{
									command.second->Execute(*controller.controlledActor);

								}

								break;

							default:

								break;
							}
						
						}


						controller.state = currentState;

					}

				}

				else
				{
					//Controller was disconnected since last check, set controller as non-existant
					controller.exists = false;

				}
			}
		
			++dwordIndex;
		}

	}
	

	void AssignActorToXinputController(int controllerIndex, GameObject* actor)
	{
		m_XinputControllers[controllerIndex].controlledActor = actor;
	};

	void AssignActorToAllXinputControllers(GameObject* actor)
	{
		for (auto& controller : m_XinputControllers)
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

	std::map<TriggerButton, std::unique_ptr<Command>> m_XinputControllerCommands{};

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


			for (auto& command : m_KeyboardCommands)
			{
				if(e.key.keysym.sym == command.first.key && e.key.state == command.first.trigger && e.key.repeat == 0)
				{
					command.second->Execute(*m_Keyboards[0].controlledActor);
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
	std::map<TriggerKey, std::unique_ptr<Command>> m_KeyboardCommands{};


private:

	//elements

	std::vector<Keyboard> m_Keyboards{};
};



using namespace Engine;


// INPUT HANDLER FUNCTION IMPLEMENTATIONS

InputHandler::InputHandler() :
	m_XinputImplPointer{new XinputInputHandlerImpl()},
	m_KeyboardImplPointer{ new KeyboardInputHandlerImpl() }
{
	m_XinputImplPointer->Initialise();
	m_KeyboardImplPointer->Initialise();
}

InputHandler::~InputHandler()

{
	delete m_XinputImplPointer;
	delete m_KeyboardImplPointer;
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


void InputHandler::AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON button, XINPUT_CONTROLLER_BUTTON_STATE state, Command* commandPointer)
{
	m_XinputImplPointer->m_XinputControllerCommands.emplace(TriggerButton(button, state), std::unique_ptr<Command>(commandPointer));
}

void InputHandler::AssignCommandToKeyboardInput(SDL_KeyCode key, unsigned int state, Command* commandPointer)
{
	m_KeyboardImplPointer->m_KeyboardCommands.emplace(TriggerKey(key, state), std::unique_ptr<Command>(commandPointer));

}