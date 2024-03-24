#include "ObserverComponent.h"
#include "GameObject.h"

using namespace Engine;

ObserverComponent::ObserverComponent(GameObject* gameObjectParentPointer, const std::string& name, Event* eventFunction) :
	GameObjectComponent(COMPONENT_TYPE::ObserverComponent, name, gameObjectParentPointer),
	m_EventFunctionPointer{ std::unique_ptr<Event>(eventFunction)}
{
}



void ObserverComponent::OnNotify(GameObject* gameObject, GAME_EVENT event)
{
	m_EventFunctionPointer->Execute(m_OwnerGameObjectPointer, gameObject, event);
}
