#ifndef XINPUT_CONTROL_INFORMATION_HEADER
#define XINPUT_CONTROL_INFORMATION_HEADER
namespace Engine
{
	class GameObject;

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

		bool operator<( const TriggerButton& rhs) const
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





}

#endif