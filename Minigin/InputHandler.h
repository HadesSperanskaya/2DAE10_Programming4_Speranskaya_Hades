#include <memory>
#include <vector>
#include <map>
#include "EngineMacros.h"

#ifndef INPUT_HANDLER_HEADER
#define INPUT_HANDLER_HEADER

namespace Engine
{
	class GameObject;
	class Command;
	struct TriggerButton;
	struct TriggerKey;

	class InputHandler final
	{

	public:

		//constructor
		InputHandler();
		//destructor
		~InputHandler();

		//deleted 
		InputHandler(const InputHandler& other) = delete;
		InputHandler(InputHandler&& other) = delete;
		InputHandler& operator=(const InputHandler& other) = delete;
		InputHandler& operator=(InputHandler&& other) = delete;

		//functions

		//run this every frame
		bool ProcessInput();

		void AssignActorToXinputController(int controllerIndex, GameObject* actor);
		void AssignActorToAllXinputControllers(GameObject* actor);
		void AssignActorToFirstFreeXinputController(GameObject* actor);

		void AssignActorToKeyboard(int keyboardIndex, GameObject* actor);


		void AssignCommandToXinputControllerInput(XINPUT_CONTROLLER_BUTTON button, XINPUT_CONTROLLER_BUTTON_STATE state, Command* commandPointer);

		void AssignCommandToKeyboardInput(SDL_KeyCode key, unsigned int state, Command* commandPointer);
		

	private: 
		class XinputInputHandlerImpl;
		XinputInputHandlerImpl* m_XinputImplPointer;


		class KeyboardInputHandlerImpl;
		KeyboardInputHandlerImpl* m_KeyboardImplPointer;


	};

}

#endif