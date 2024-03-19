#include <vector>

#include "GameObjectComponent.h"

#ifndef COMPONENT_RENDER_HEADER
#define COMPONENT_RENDER_HEADER

namespace Engine
{

	class Texture2DComponent;
	class GameObject;
	struct Transform;

    class RenderComponent final : public GameObjectComponent
    {
	public: 
		//constructor
		RenderComponent(GameObject* gameObjectParentPointer);

		//destructor
		~RenderComponent() = default;

		//copy and move constructors and assignment operators
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;


		//functions
		void Render(const Transform& transform) const;
		void RenderUI(const Transform& transform);

		void AddComponentToRender(GameObjectComponent* componentToAdd);

		void EraseEmptyComponents();


	private:
		//explicitly deleted default constructor
		RenderComponent() = delete;

		//elements
		std::vector<GameObjectComponent*> m_ComponentPointersVector;



    };
}

#endif