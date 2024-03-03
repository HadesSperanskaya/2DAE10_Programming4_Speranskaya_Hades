#include "TransformComponent.h"


using namespace Engine;

TransformComponent::TransformComponent(GameObject* gameObjectParentPointer, const glm::vec3& position, float rotation)
	:
	GameObjectComponent(COMPONENT_TYPE::TransformComponent, COMPONENT_TYPENAME_TRANSFORM, gameObjectParentPointer),
	m_Rotation{ rotation},
	m_Position{position}
{

};

