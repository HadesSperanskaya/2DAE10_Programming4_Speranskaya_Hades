#pragma once
#include <memory>
#include "GameObjectComponent.h"

namespace Engine
{

	class Texture2D;


	class Texture2DComponent final : public GameObjectComponent
	{
	public:

		//constructor
		Texture2DComponent(GameObject* gameObjectParentPointer, const std::string& name, Texture2D* texturePointer = nullptr);

		//destructor
		~Texture2DComponent() = default;

		//copy/assignment constructor and move functions
		Texture2DComponent(const Texture2DComponent& other) = delete;
		Texture2DComponent(Texture2DComponent&& other) = delete;
		Texture2DComponent& operator=(const Texture2DComponent& other) = delete;
		Texture2DComponent& operator=(Texture2DComponent&& other) = delete;


		void Render(float xPosition, float yPosition, float rotation) const;


		//elements
		Texture2D* m_TexturePointer{};


	private:

	};

}
