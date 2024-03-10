#include "RenderComponent.h"

using namespace Engine;

RenderComponent::RenderComponent(GameObject* gameObjectParentPointer) :
	GameObjectComponent(COMPONENT_TYPE::RenderComponent, COMPONENT_TYPENAME_RENDER, gameObjectParentPointer)
{

}



void RenderComponent::Render(float xPosition, float yPosition, float rotation) const
{
	for (auto& component : m_ComponentPointersVector)
	{
		if(component)
		{
			component->Render(xPosition, yPosition, rotation);
		}
	}
}

void RenderComponent::AddComponentToRender(GameObjectComponent* componentToAdd)
{
	if(componentToAdd)
	{
		if(componentToAdd->m_OwnerGameObjectPointer == m_OwnerGameObjectPointer)
		{
			m_ComponentPointersVector.push_back(componentToAdd);
		}
	}
}

void RenderComponent::EraseEmptyComponents()
{
	//remove and erase all components that are now nullptr

	m_ComponentPointersVector.erase(std::remove_if(m_ComponentPointersVector.begin(), m_ComponentPointersVector.end(), [](const GameObjectComponent* component) {return (component == nullptr); }),
									m_ComponentPointersVector.end());



}
