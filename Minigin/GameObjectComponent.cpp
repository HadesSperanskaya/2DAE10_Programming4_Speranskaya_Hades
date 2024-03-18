#include "GameObjectComponent.h"
#include "TransformComponent.h"

using namespace Engine;

GameObjectComponent::GameObjectComponent(COMPONENT_TYPE componentType, const std::string& componentName, GameObject* gameObjectParentPointer) :
	m_OwnerGameObjectPointer(gameObjectParentPointer),
	m_ComponentType(componentType),
	m_ComponentName(componentName)
{

};

