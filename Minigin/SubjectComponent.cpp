#include "SubjectComponent.h"
#include "ObserverComponent.h"
#include "GameObject.h"

using namespace Engine;

SubjectComponent::SubjectComponent(GameObject* gameObjectParentPointer) :
	GameObjectComponent(COMPONENT_TYPE::SubjectComponent, COMPONENT_TYPENAME_SUBJECT, gameObjectParentPointer)
{

}


void SubjectComponent::AddObserver(ObserverComponent* observer, GameObjectComponent* interestingComponent)
{
	if(observer && interestingComponent)
	{
		m_ObserversPointers.emplace(observer, interestingComponent);
		m_NumberOfObservers = int(m_ObserversPointers.size());
	}
}

void SubjectComponent::RemoveObserver(ObserverComponent* observer, GameObjectComponent* interestingComponent)
{
	if (observer)
	{
		m_ObserversPointers.erase(std::pair<ObserverComponent*, GameObjectComponent*>(observer, interestingComponent));
		m_NumberOfObservers = int(m_ObserversPointers.size());
	}
}


void SubjectComponent::NotifyObservers(GameObject* gameObject, GameObjectComponent* notifyingComponent, GAME_EVENT event)
{
	if (m_NumberOfObservers > 0)
	{
		for (auto observer : m_ObserversPointers)
		{
			if(observer.second == notifyingComponent)
			{
				observer.first->OnNotify(gameObject, event);
			}
		}
	}
}