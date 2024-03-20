#include <glm/glm.hpp>

#include "GameObjectComponent.h"


#ifndef COMPONENT_TRANSFORM_HEADER
#define COMPONENT_TRANSFORM_HEADER

namespace Engine
{
	class GameObject;

	struct Transform
	{
		glm::vec2 position{ 0.f, 0.f};
		float rotation{ 0 };
		//glm::vec2 scale{ 0, 0};
	};



	class TransformComponent final : public GameObjectComponent
	{
	public:

		//constructor 
		TransformComponent(GameObject* gameObjectParentPointer);
		//destructor
		~TransformComponent() = default;

		//deleted
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;


		//functions
		void UpdateDueToNewParentAssigned(GameObject* parent);
		void UpdateDueToParentBeingTransformed();

		//elements
		static const Transform m_WorldOrigin;

		Transform m_Local;
		const Transform* m_World; //does not own that transform, only points to it
		Transform m_Combined;

		PARENT_CHILD_TRANSFORM_RELATIONSHIP m_NewParentTransformInheritParameters{};
		PARENT_CHILD_TRANSFORM_RELATIONSHIP m_UpdatedParentTransformInheritParameters{};

	private:
		//explicitly deleted default constructor
		TransformComponent() = delete;

	};
}

#endif