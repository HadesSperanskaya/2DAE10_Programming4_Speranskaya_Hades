#include "LocomotionComponent.h"
#include "EngineMacros.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "Scene.h"

using namespace Engine;


LocomotionComponent::LocomotionComponent(GameObject* gameObjectParentPointer, const std::string& name, float baseSpeed)
	:
	GameObjectComponent(COMPONENT_TYPE::LocomotionComponent, name, gameObjectParentPointer),
	m_BaseSpeed{baseSpeed}
{

};


void LocomotionComponent::Update()
{

	if ((m_Velocity.x * m_Velocity.x + m_Velocity.y + m_Velocity.y) > 1)
	{
		const glm::vec2 updatedPosition = m_OwnerGameObjectPointer->GetTransformComponent()->m_Local.position + glm::normalize(m_Velocity) * (Scene::m_DeltaTime * m_BaseSpeed);
		m_OwnerGameObjectPointer->SetLocalPosition(updatedPosition.x, updatedPosition.y);
	}
	else
	{
		const glm::vec2 updatedPosition = m_OwnerGameObjectPointer->GetTransformComponent()->m_Local.position + m_Velocity * (Scene::m_DeltaTime * m_BaseSpeed);
		m_OwnerGameObjectPointer->SetLocalPosition(updatedPosition.x, updatedPosition.y);

	}


}

void LocomotionComponent::AddVelocity(glm::vec2& velocity)
{
	m_Velocity += velocity;



}