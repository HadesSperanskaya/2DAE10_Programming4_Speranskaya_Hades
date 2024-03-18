#include <glm/glm.hpp>

#include "GameObjectComponent.h"


#ifndef COMPONENT_TRANSFORM_HEADER
#define COMPONENT_TRANSFORM_HEADER

namespace Engine
{

	struct Transform
	{
		glm::vec3 position{ 0.f, 0.f, 0.f };
		float rotation{ 0 };
		glm::vec2 scale{ 0, 0 };
	};



	class TransformComponent final : public GameObjectComponent
	{
	public:

		//constructor 
		TransformComponent(GameObject* gameObjectParentPointer);
	

		//destructor
		virtual ~TransformComponent() = default;

		//copy and move constructor and assignment operators
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		void UpdateDueToNewParentAssigned(GameObject* parent);
		void UpdateDueToParentBeingTransformed();


		//elements - public following the guideline "C.131: Avoid trivial getters and setters"

		static const Transform m_WorldOrigin;

		Transform m_Local;
		const Transform* m_World;
		Transform m_Combined;


		//structs holding info on how to handle transforms relating to parent stuff
		PARENT_CHILD_TRANSFORM_RELATIONSHIP m_NewParentTransformInheritParameters{};
		PARENT_CHILD_TRANSFORM_RELATIONSHIP m_UpdatedParentTransformInheritParameters{};

	private:
		

	};
}

#endif