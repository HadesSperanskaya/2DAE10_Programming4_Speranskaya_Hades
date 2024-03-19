#include <memory>
#include <vector>
#include <map>

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
		~InputHandler() = default;

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


		//void AssignCommandToXinputControllerInput(TriggerButton triggerButton, Command* commandPointer);

		//void AssignCommandToKeyboardInput(TriggerKey triggerButton, Command* commandPointer);
		

	private: 
		class XinputInputHandlerImpl;
		std::unique_ptr<XinputInputHandlerImpl> m_XinputImplPointer;


		class KeyboardInputHandlerImpl;
		std::unique_ptr<KeyboardInputHandlerImpl> m_KeyboardImplPointer;


	};

}

#endif