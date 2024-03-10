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
	m_OrbitTargetTransformPointer = gameObjectParentPointer->GetWorldTransformComponent();
}


void RotatorComponent::Update(float deltaTime)
{
	//if both pointers are valid - target and object that is doing the orbiting
	if (m_OrbitTargetTransformPointer)
	{
		float totalRotation = m_OwnerGameObjectPointer->GetLocalTransformComponent()->m_Rotation + m_AngularVeloctiy * deltaTime;

		if (totalRotation > PI_TIMES_TW0_VALUE)
		{
			do
			{
				totalRotation = float(totalRotation - PI_TIMES_TW0_VALUE);
			} while (totalRotation > PI_TIMES_TW0_VALUE);
		}
		else if (totalRotation < 0)
		{
			totalRotation = float(PI_TIMES_TW0_VALUE - totalRotation);
		}
		m_OwnerGameObjectPointer->SetRotation(totalRotation);

		m_OwnerGameObjectPointer->SetPosition(std::sinf(totalRotation) * m_OrbitRadius,
											  std::cosf(totalRotation) * m_OrbitRadius);

	}
}


