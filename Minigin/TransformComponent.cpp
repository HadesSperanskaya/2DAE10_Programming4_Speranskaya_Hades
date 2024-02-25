#include "TransformComponent.h"

dae::TransformComponent::TransformComponent()
	:
	GameObjectComponent(COMPONENT_TYPENAME_TRANSFORM, COMPONENT_TYPENAME_TRANSFORM)
{

	m_Position.x = 0;
	m_Position.y = 0;
	m_Position.z = 0;

};

dae::TransformComponent::TransformComponent(const glm::vec3& position)
	:
	GameObjectComponent(COMPONENT_TYPENAME_TRANSFORM, COMPONENT_TYPENAME_TRANSFORM)
{
	m_Position = position;
};


const glm::vec3& dae::TransformComponent::GetPosition() const
{
	return m_Position;
};


void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
};
