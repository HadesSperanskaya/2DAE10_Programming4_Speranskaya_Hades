#include "HealthComponent.h"
#include "GameObject.h"
#include "SubjectComponent.h"


using namespace Engine;


HealthComponent::HealthComponent(GameObject* gameObjectParentPointer, int maxHealth, int maxLives)
	:
	GameObjectComponent(COMPONENT_TYPE::HealthComponent, COMPONENT_TYPENAME_HEALTH, gameObjectParentPointer),
	m_CurrentHealth{ maxHealth },
	m_CurrentLives{ maxLives },
	m_IsDying{false},
	m_IsDead{false},
	m_MaxHealth{ maxHealth },
	m_MaxLives{ maxLives }

{

}


void HealthComponent::Update()
{

	if (m_IsDying)
	{
		//do death animation. once death animation done, set m_IsDead to true, and kill owning game object
	}



};

void HealthComponent::TakeDamage(int damage)
{
	m_CurrentHealth = m_CurrentHealth - damage;
	if (m_CurrentHealth <= 0)
	{
		m_CurrentLives = m_CurrentLives - 1;

		GameObjectComponent* subjectPointer{ m_OwnerGameObjectPointer->GetComponentByType(COMPONENT_TYPE::SubjectComponent) };

		if (subjectPointer)
		{
			(static_cast<SubjectComponent*>(subjectPointer))->NotifyObservers(m_OwnerGameObjectPointer, this, GAME_EVENT::ENTITY_LOST_LIFE);
		}



	}
	if (m_CurrentLives <= 0)
	{
		m_IsDying = true;

		GameObjectComponent* subjectPointer{ m_OwnerGameObjectPointer->GetComponentByType(COMPONENT_TYPE::SubjectComponent) };

		if (subjectPointer)
		{
			(static_cast<SubjectComponent*>(subjectPointer))->NotifyObservers(m_OwnerGameObjectPointer, this, GAME_EVENT::ENTITY_DIED);
		}
	}
};

void HealthComponent::KillOwningGameObject()
{
	//implement setting the destruction flag on owner

};