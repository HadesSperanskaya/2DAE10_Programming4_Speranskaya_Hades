#pragma once
#include "GameObjectComponent.h"
#include <memory>

namespace dae
{

	class Texture2D;


	class Texture2DComponent final : public GameObjectComponent
	{
	public:

		Texture2DComponent(const std::string& name);
		Texture2DComponent(const std::string& name, std::shared_ptr<Texture2D> textureSharedPointer);
		~Texture2DComponent() = default;


		Texture2DComponent(const Texture2DComponent& other) = delete;
		Texture2DComponent(Texture2DComponent&& other) = delete;
		Texture2DComponent& operator=(const Texture2DComponent& other) = delete;
		Texture2DComponent& operator=(Texture2DComponent&& other) = delete;

		void Render(float x, float y) const;

		const std::shared_ptr<Texture2D> GetTexture() const;

		void SetTexture(std::shared_ptr<Texture2D> textureSharedPointer);



	private:

		std::shared_ptr<Texture2D> m_TextureSharedPointer{};

	};

}
