#include "EngineMacros.h"


#ifndef EVENT_BASE_HEADER
#define EVENT_BASE_HEADER

namespace Engine
{
	class GameObject;

	class Event
	{
	public:
		virtual ~Event() = default;
		virtual void Execute(GameObject* observer, GameObject* subject, GAME_EVENT event) = 0;
	};


}

#endif