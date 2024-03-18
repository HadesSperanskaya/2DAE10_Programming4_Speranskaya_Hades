#include "GameObjectComponent.h"

#ifndef COMPONENT_ROTATOR_HEADER
#define COMPONENT_ROTATOR_HEADER
namespace Engine
{
	class TransformComponent;

    class RotatorComponent: public GameObjectComponent
    {

	public:
		//constructor
		RotatorComponent(GameObject* gameObjectParentPointer, const std::string& name);

		//destructor
		~RotatorComponent() = default;

		//copy and move constructors and assignment operators
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;


		//functions
		virtual void Update(float deltaTime);



		//elements
		float m_AngularVeloctiy{1};
		float m_OrbitRadius{50};

		//const so that the qualities of the target cannot be changed
		const Transform* m_OrbitTargetTransformPointer;


	private:
		//functions
		RotatorComponent() = delete;
		//elements


    };
}

#endif