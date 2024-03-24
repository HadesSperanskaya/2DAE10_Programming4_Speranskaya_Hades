#include <set>
#include "GameObjectComponent.h"

#ifndef COMPONENT_SUBJECT_HEADER
#define COMPONENT_SUBJECT_HEADER

namespace Engine
{
	class GameObject;
	class ObserverComponent;

	class SubjectComponent final : public GameObjectComponent
	{
	public:
		//functions
		SubjectComponent(GameObject* gameObjectParentPointer);
		~SubjectComponent() = default;

		SubjectComponent(const SubjectComponent& other) = delete;
		SubjectComponent(SubjectComponent&& other) = delete;
		SubjectComponent& operator=(const SubjectComponent& other) = delete;
		SubjectComponent& operator=(SubjectComponent&& other) = delete;


		void AddObserver(ObserverComponent* observer, GameObjectComponent* interestingComponent);
		void RemoveObserver(ObserverComponent* observer, GameObjectComponent* interestingComponent);

		void NotifyObservers(GameObject* gameObject, GameObjectComponent* notifyingComponent, GAME_EVENT event);

	protected:

		std::set<std::pair<ObserverComponent*, GameObjectComponent*>> m_ObserversPointers;
		int m_NumberOfObservers{ 0 };




	};

}



#endif