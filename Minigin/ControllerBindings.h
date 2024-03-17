#pragma once
#include "Command.h"

namespace Engine
{
	struct ControllerBindings
	{
		//controller bindings
		Command* buttonXPressed{ nullptr };
		Command* buttonXReleased{ nullptr };
		Command* buttonXHeld{ nullptr };

		Command* buttonYPressed{ nullptr };
		Command* buttonYReleased{ nullptr };
		Command* buttonYHeld{ nullptr };

		Command* buttonAPressed{ nullptr };
		Command* buttonAReleased{ nullptr };
		Command* buttonAHeld{ nullptr };

		Command* buttonBPressed{ nullptr };
		Command* buttonBReleased{ nullptr };
		Command* buttonBHeld{ nullptr };


		Command* dpadUpHeld{ nullptr };
		Command* dpadDownHeld{ nullptr };
		Command* dpadLeftHeld{ nullptr };
		Command* dpadRightHeld{ nullptr };

		Command* start{ nullptr };
		Command* back{ nullptr };



		//set commands
		void SetCommandButtonXPressed(Command* commandPointer)
		{
			buttonXPressed = commandPointer;
		};

		void SetCommandButtonXReleased(Command* commandPointer)
		{
			buttonXReleased = commandPointer;
		};

		void SetCommandButtonXHeld(Command* commandPointer)
		{
			buttonXHeld = commandPointer;
		};


		void SetCommandButtonYPressed(Command* commandPointer)
		{
			buttonYPressed = commandPointer;
		};

		void SetCommandButtonYReleased(Command* commandPointer)
		{
			buttonYReleased= commandPointer;
		};

		void SetCommandButtonYHeld(Command* commandPointer)
		{
			buttonYHeld = commandPointer;
		};


		void SetCommandButtonAPressed(Command* commandPointer)
		{
			buttonAPressed = commandPointer;
		};

		void SetCommandButtonAReleased(Command* commandPointer)
		{
			buttonAReleased = commandPointer;
		};

		void SetCommandButtonAHeld(Command* commandPointer)
		{
			buttonAHeld = commandPointer;
		};




		void SetCommandButtonBPressed(Command* commandPointer)
		{
			buttonBPressed = commandPointer;
		};

		void SetCommandButtonBReleased(Command* commandPointer)
		{
			buttonXReleased = commandPointer;
		};

		void SetCommandButtonBHeld(Command* commandPointer)
		{
			buttonBHeld = commandPointer;
		};




		void SetCommandDpadUpHeld(Command* commandPointer)
		{
			dpadUpHeld = commandPointer;
		};

		void SetCommandDpadDownHeld(Command* commandPointer)
		{
			dpadDownHeld = commandPointer;
		};

		void SetCommandDpadLeftHeld(Command* commandPointer)
		{
			dpadLeftHeld = commandPointer;
		};

		void SetCommandDpadRightHeld(Command* commandPointer)
		{
			dpadRightHeld = commandPointer;
		};


		void SetCommandStart(Command* commandPointer)
		{
			start = commandPointer;
		};

		void SetCommandBack(Command* commandPointer)
		{
			back = commandPointer;
		};










	};
}

