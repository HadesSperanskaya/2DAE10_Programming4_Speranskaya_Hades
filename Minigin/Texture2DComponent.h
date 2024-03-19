#include <memory>
#include "GameObjectComponent.h"

#ifndef COMPONENT_TEXTURE2D_HEADER
#define COMPONENT_TEXTURE2D_HEADER

namespace Engine
{
	class GameObject;
	class Texture2D;
	struct Transform;

	class Texture2DComponent final : public GameObjectComponent
	{
	public:

		//constructor
		Texture2DComponent(GameObject* gameObjectParentPointer, const std::string& name, Texture2D* texturePointer);

		//destructor
		~Texture2DComponent() = default;

		//copy/assignment constructor and move functions
		Texture2DComponent(const Texture2DComponent& other) = delete;
		Texture2DComponent(Texture2DComponent&& other) = delete;
		Texture2DComponent& operator=(const Texture2DComponent& other) = delete;
		Texture2DComponent& operator=(Texture2DComponent&& other) = delete;


		void Render(const Transform& transform) const;


		//elements
		Texture2D* m_TexturePointer{};


	private:
		//explicitly deleted default constructor
		Texture2DComponent() = delete;


	};

}

#endif