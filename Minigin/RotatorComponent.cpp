#include "TransformComponent.h"
#include "RotatorComponent.h"
#include "GameObject.h"

using namespace Engine;

RotatorComponent::RotatorComponent(GameObject* gameObjectParentPointer, const std::string& name)
	:
	GameObjectComponent(COMPONENT_TYPE::RotatorComponent, name, gameObjectParentPointer)
{
	m_OrbitTargetTransformPointer = &gameObjectParentPointer->GetTransformComponent()->m_Combined;
}


void RotatorComponent::Update(float deltaTime)
{
	//if both pointers are valid - target and object that is doing the orbiting
	if (m_OrbitTargetTransformPointer)
	{
		float totalRotation = m_OwnerGameObjectPointer->GetTransformComponent()->m_Local.rotation + m_AngularVeloctiy * deltaTime;

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
		m_OwnerGameObjectPointer->SetLocalRotation(totalRotation);

		m_OwnerGameObjectPointer->SetLocalPosition(std::sinf(totalRotation) * m_OrbitRadius, std::cosf(totalRotation) * m_OrbitRadius);

	}
}


