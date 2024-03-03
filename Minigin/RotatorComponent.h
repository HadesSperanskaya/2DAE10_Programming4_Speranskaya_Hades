#pragma once
#include "GameObjectComponent.h"


namespace Engine
{
	class TransformComponent;

    class RotatorComponent: public GameObjectComponent
    {

	public:
		//constructor
		RotatorComponent(GameObject* gameObjectParentPointer, const std::string& name, float angularVelocity = 1.f, float orbitRadius = 50.f);

		//destructor
		~RotatorComponent() = default;

		//copy and move constructors and assignment operators
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;


		//functions
		void Update(float deltaTime);



		//elements
		float m_AngularVeloctiy{};
		float m_OrbitRadius{};
		std::weak_ptr<TransformComponent> m_OrbitTargetTransformPointer;
		std::weak_ptr<TransformComponent> m_OrbitingTransformComponentPointer;





	private:

		//elements


    };
}

