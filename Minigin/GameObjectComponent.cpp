#include <string>
#include "GameObjectComponent.h"

dae::GameObjectComponent::GameObjectComponent(std::string componentTypeName, std::string componentName) :
	m_ComponentTypeName(componentTypeName),
	m_ComponentUniqueName(componentName),
	m_IsRenderable(false)
{
	
};

void dae::GameObjectComponent::Update(float deltaTime) 
{
	deltaTime;
};

void dae::GameObjectComponent::Render(float x, float y) const 
{
	x;
	y;
};

const std::string& dae::GameObjectComponent::GetComponentTypeName() const
{
	return m_ComponentTypeName;
};

const std::string& dae::GameObjectComponent::GetComponentName() const
{
	return m_ComponentUniqueName;
};

bool dae::GameObjectComponent::GetIsRenderable() const
{
	return m_IsRenderable;
};

void dae::GameObjectComponent::SetComponentName(const std::string& newName)
{
	m_ComponentUniqueName = newName;
};

void dae::GameObjectComponent::SetRenderable(bool isRenderable)
{
	m_IsRenderable = isRenderable;
};