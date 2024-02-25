#pragma once
#include <glm/glm.hpp>
#include "GameObjectComponent.h"

namespace dae
{
	class TransformComponent final : public GameObjectComponent
	{
	public:

		TransformComponent();
		TransformComponent(const glm::vec3& position);

		const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z);



	private:
		glm::vec3 m_Position;

	};
}
