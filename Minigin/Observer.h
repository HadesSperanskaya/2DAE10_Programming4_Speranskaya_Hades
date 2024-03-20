#include "EngineMacros.h"

#ifndef OBSERVER_HEADER
#define OBSERVER_HEADER

namespace Engine
{
	class GameObject;
	class Observer
	{
	public:
		//functions
		Observer() = default;
		virtual ~Observer() = default;

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;


		virtual void OnNotify(GameObject* gameObject, GAME_EVENT event) = 0;

	private:



	};

}

#endif