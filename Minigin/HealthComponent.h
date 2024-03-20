
#include "GameObjectComponent.h"

#ifndef COMPONENT_HEALTH_HEADER
#define COMPONENT_HEALTH_HEADER

namespace Engine
{
    class HealthComponent : public GameObjectComponent
    {

	public:
		//constructor
		HealthComponent(GameObject* gameObjectParentPointer, int maxHealth, int maxLives);

		//destructor
		~HealthComponent() = default;

		//copy/assignment constructor and move functions
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;
		

		void Update();

		void TakeDamage(int damage);

		void KillOwningGameObject();

		int m_CurrentHealth;
		int m_CurrentLives;
		bool m_IsDying;
		bool m_IsDead;

	private:
		//explicitly deleted default constructor
		HealthComponent() = delete;

		const int m_MaxHealth;
		const int m_MaxLives;


    };

}

#endif