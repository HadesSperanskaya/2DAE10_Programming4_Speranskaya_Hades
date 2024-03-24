#include <memory.h>
#include "GameObjectComponent.h"
#include "Event.h"


#ifndef OBSERVER_HEADER
#define OBSERVER_HEADER

namespace Engine
{
	class GameObject;

	class ObserverComponent final : public GameObjectComponent
	{
	public:
		//functions
		ObserverComponent(GameObject* gameObjectParentPointer, const std::string& name, Event* eventFunction);
		virtual ~ObserverComponent() = default;

		ObserverComponent(const ObserverComponent& other) = delete;
		ObserverComponent(ObserverComponent&& other) = delete;
		ObserverComponent& operator=(const ObserverComponent& other) = delete;
		ObserverComponent& operator=(ObserverComponent&& other) = delete;

		void OnNotify(GameObject* gameObject, GAME_EVENT event);


		std::unique_ptr<Event> m_EventFunctionPointer;



	private:



	};

}

#endif