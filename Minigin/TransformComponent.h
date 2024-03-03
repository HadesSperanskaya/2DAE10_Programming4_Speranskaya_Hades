#pragma once
#include <glm/glm.hpp>
#include "GameObjectComponent.h"

namespace Engine
{

	class TransformComponent final : public GameObjectComponent
	{
	public:

		//constructor 
		TransformComponent(GameObject* gameObjectParentPointer, const glm::vec3& position = glm::vec3{0.f, 0.f, 0.f}, float rotation = 0.f);
	

		//destructor
		~TransformComponent() = default;

		//copy and move constructor and assignment operators
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;


		//elements - public following the guideline "C.131: Avoid trivial getters and setters"
		glm::vec3 m_Position;
		float m_Rotation;



	private:
		

	};
}
