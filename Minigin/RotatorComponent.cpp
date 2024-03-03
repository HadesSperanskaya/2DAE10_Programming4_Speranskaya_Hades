#include "TransformComponent.h"
#include "RotatorComponent.h"
#include "GameObject.h"

using namespace Engine;

RotatorComponent::RotatorComponent(GameObject* gameObjectParentPointer, const std::string& name, float angularVelocity, float orbitRadius)
	:
	GameObjectComponent(COMPONENT_TYPE::RotatorComponent, name, gameObjectParentPointer),
	m_AngularVeloctiy(angularVelocity),
	m_OrbitRadius(orbitRadius)
{
	m_OrbitingTransformComponentPointer = gameObjectParentPointer->GetLocalTransformComponent();
	m_OrbitTargetTransformPointer = gameObjectParentPointer->GetWorldTransformComponent();
}


void RotatorComponent::Update(float deltaTime)
{
	if (m_OrbitingTransformComponentPointer.expired() != true && m_OrbitTargetTransformPointer.expired() != true)
	{
		const float totalRotation = std::shared_ptr<TransformComponent>(m_OrbitingTransformComponentPointer)->m_Rotation + m_AngularVeloctiy * deltaTime;

		const float displacementX = std::sinf(totalRotation) * m_OrbitRadius;
		const float displacementY = std::cosf(totalRotation) * m_OrbitRadius;
	
		m_OwnerGameObjectPointer->SetRotation(totalRotation);

		m_OwnerGameObjectPointer->SetPosition(displacementX, displacementY);

	}
}


