#pragma once
#include "Singleton.h"
#include <Xinput.h>

namespace Engine
{
	class InputManager final : public Singleton<InputManager>
	{


	public:
		bool ProcessInput();


	private:
		XINPUT_STATE m_CurrentState;

	};

}
