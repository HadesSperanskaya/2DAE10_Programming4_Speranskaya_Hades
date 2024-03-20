#include "GameObjectComponent.h"

#ifndef COMPONENT_ORBIT_HEADER
#define COMPONENT_ORBIT_HEADER
namespace Engine
{
	class TransformComponent;
	class GameObject;

    class OrbitComponent final: public GameObjectComponent
    {

	public:
		//constructor
		OrbitComponent(GameObject* gameObjectParentPointer, const std::string& name);

		//destructor
		~OrbitComponent() = default;

		//copy and move constructors and assignment operators
		OrbitComponent(const OrbitComponent& other) = delete;
		OrbitComponent(OrbitComponent&& other) = delete;
		OrbitComponent& operator=(const OrbitComponent& other) = delete;
		OrbitComponent& operator=(OrbitComponent&& other) = delete;


		//functions
		void Update();


		//elements
		float m_AngularVeloctiy{1};
		float m_OrbitRadius{50};

		//const so that the qualities of the target cannot be changed
		const Transform* m_OrbitTargetTransformPointer;


	private:
		//explicitly deleted default constructor
		OrbitComponent() = delete;

		float m_RotationAngle{ 0 };

    };
}

#endif