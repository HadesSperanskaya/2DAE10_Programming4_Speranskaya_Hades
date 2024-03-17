#pragma once
#include <Xinput.h>
#include <vector>
#include "ControllerBindings.h"


namespace Engine
{
	class GameObject;
	struct Controller
	{
		bool exists{ false };
		XINPUT_STATE state{};
		GameObject* controlledActor{nullptr};
	};



	class InputManager final
	{

	public:

		//functions
		InputManager();

		//run this every few seconds, not every frame
		void CheckForNewControllers();

		//run this every frame
		bool ProcessInput();

		void AssignActorToAnyController(int controllerIndex, GameObject* actor);
		void AssignActorToAllControllers(GameObject* actor);
		void AssignActorToFirstFreeController(GameObject* actor);

		//elements
		//controller bindings
		ControllerBindings m_ControllerBindings;


	private:

		//functions
		bool IsDownThisFrame(WORD buttonsPressedThisFrame, unsigned int button) const;
		bool IsUpThisFrame(WORD buttonsReleasedThisFrame, unsigned int button) const;
		bool IsPressed(WORD stateOfButtons, unsigned int button) const;


		//elements
		std::vector<Controller> m_Controllers;



	};

}
