#include "RenderComponent.h"

using namespace Engine;

RenderComponent::RenderComponent() :
	GameObjectComponent(COMPONENT_TYPE::RenderComponent, COMPONENT_TYPENAME_RENDER)
{

}



void RenderComponent::Render(float xPosition, float yPosition, float rotation) const
{
	for (auto& component : m_ComponentWeakPointersVector)
	{
		if(component.expired() != true)
		{
			std::shared_ptr<GameObjectComponent>(component)->Render(xPosition, yPosition, rotation);
		}
	}
}

void RenderComponent::AddComponentToRender(std::shared_ptr<GameObjectComponent> componentToAdd)
{
	if(componentToAdd != nullptr)
	{
		m_ComponentWeakPointersVector.push_back(std::weak_ptr<GameObjectComponent>(componentToAdd));
	}
}

void RenderComponent::EraseEmptyComponents()
{
	//remove and erase all expired pointers. the remove if return the iterator to the logical end, 
	//where all the expired pointers are moved during the remove_if function

	m_ComponentWeakPointersVector.erase(std::remove_if(m_ComponentWeakPointersVector.begin(), m_ComponentWeakPointersVector.end(),
										[](std::weak_ptr<GameObjectComponent> element) 
											{
												return (element.use_count() == 0); 
											}), m_ComponentWeakPointersVector.end());



}
