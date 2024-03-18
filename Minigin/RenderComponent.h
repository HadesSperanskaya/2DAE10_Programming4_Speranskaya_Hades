#include <vector>

#include "GameObjectComponent.h"

#ifndef COMPONENT_RENDER_HEADER
#define COMPONENT_RENDER_HEADER

namespace Engine
{

	class Texture2DComponent;
	struct Transform;

    class RenderComponent : public GameObjectComponent
    {
	public: 
		//constructor
		RenderComponent(GameObject* gameObjectParentPointer);

		//destructor
		virtual ~RenderComponent() = default;

		//copy and move constructors and assignment operators
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;


		//functions


		virtual void Render(const Transform& transform) const;
		virtual void RenderUI(const Transform& transform);

		void AddComponentToRender(GameObjectComponent* componentToAdd);

		void EraseEmptyComponents();


	private:
		//functions, explicitly deleted constructor
		RenderComponent() = delete;

		//elements
		//render component only needs to call the render functions of the renderable components
		std::vector<GameObjectComponent*> m_ComponentPointersVector;



    };
}

#endif