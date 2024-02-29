#pragma once
#include "GameObjectComponent.h"
#include <memory>

namespace Engine
{

	class Texture2D;


	class Texture2DComponent final : public GameObjectComponent
	{
	public:

		//constructor
		Texture2DComponent(const std::string& name, std::shared_ptr<Texture2D> textureSharedPointer = nullptr);

		//destructor
		~Texture2DComponent() = default;

		//copy/assignment constructor and move functions
		Texture2DComponent(const Texture2DComponent& other) = delete;
		Texture2DComponent(Texture2DComponent&& other) = delete;
		Texture2DComponent& operator=(const Texture2DComponent& other) = delete;
		Texture2DComponent& operator=(Texture2DComponent&& other) = delete;


		void Render(float xPosition, float yPosition, float rotation) const;



		//element - public following the guideline "C.131: Avoid trivial getters and setters"
		std::shared_ptr<Texture2D> m_TextureSharedPointer{};




	private:

	};

}
