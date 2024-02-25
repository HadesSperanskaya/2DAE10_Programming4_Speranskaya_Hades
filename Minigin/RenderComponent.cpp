#include "RenderComponent.h"


dae::RenderComponent::RenderComponent() :
	GameObjectComponent(COMPONENT_TYPENAME_RENDER, COMPONENT_TYPENAME_RENDER)
{

}



void dae::RenderComponent::Render(float x, float y) const
{
	for (auto& component : m_ObjectsToRenderVector)
	{
		component->Render(x, y);
	}
}

void dae::RenderComponent::AddComponentToRender(GameObjectComponent* objectToRender)
{
	m_ObjectsToRenderVector.push_back(objectToRender);
}

void dae::RenderComponent::RemoveComponentToRenderByName(const std::string& componentName)
{
	for (int vectorIndex{ 0 }; vectorIndex < int(m_ObjectsToRenderVector.size()); ++vectorIndex)
	{
		if (m_ObjectsToRenderVector[vectorIndex]->GetComponentName() == componentName)
		{
			m_ObjectsToRenderVector.erase(std::find(m_ObjectsToRenderVector.begin(), m_ObjectsToRenderVector.end(), m_ObjectsToRenderVector[vectorIndex]));
		}
	}
}
