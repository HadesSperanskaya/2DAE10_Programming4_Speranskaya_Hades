#include "TransformComponent.h"


using namespace Engine;

TransformComponent::TransformComponent(const glm::vec3& position, float rotation)
	:
	GameObjectComponent(COMPONENT_TYPE::TransformComponent, COMPONENT_TYPENAME_TRANSFORM),
	m_Rotation{ rotation},
	m_Position{position}
{

};

