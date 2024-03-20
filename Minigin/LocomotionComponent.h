#include <glm/glm.hpp>
#include "GameObjectComponent.h"


#ifndef COMPONENT_LOCOMOTION_HEADER
#define COMPONENT_LOCOMOTION_HEADER

namespace Engine
{
	class LocomotionComponent : public GameObjectComponent
	{
	public:

		//constructor
		LocomotionComponent(GameObject* gameObjectParentPointer, const std::string& name, float baseSpeed);

		//destructor
		~LocomotionComponent() = default;

		//copy/assignment constructor and move functions
		LocomotionComponent(const LocomotionComponent& other) = delete;
		LocomotionComponent(LocomotionComponent&& other) = delete;
		LocomotionComponent& operator=(const LocomotionComponent& other) = delete;
		LocomotionComponent& operator=(LocomotionComponent&& other) = delete;


		void Update();
		void AddVelocity(glm::vec2& velocity);

		glm::vec2 m_Velocity{0.f, 0.f};


	private:
		//explicitly deleted default constructor
		LocomotionComponent() = delete;


		const float m_BaseSpeed;


	};

}

#endif