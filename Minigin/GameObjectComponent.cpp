#include "GameObjectComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

using namespace Engine;

GameObjectComponent::GameObjectComponent(COMPONENT_TYPE componentType, const std::string& componentName, GameObject* gameObjectParentPointer) :
	m_OwnerGameObjectPointer(gameObjectParentPointer),
	m_ComponentType(componentType),
	m_ComponentName(componentName)
{

};

void GameObjectComponent::Update()
{

}

void GameObjectComponent::Render(const Transform& transform) const
{
	transform;
}
void GameObjectComponent::RenderUI(const Transform& transform)
{
	transform;
}
