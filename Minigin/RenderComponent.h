#pragma once
#include "GameObjectComponent.h"
#include <vector>

namespace Engine
{

	class Texture2DComponent;

    class RenderComponent : public GameObjectComponent
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


		void Render(float xPosition, float yPosition, float rotation) const;
		void RenderUI(float xPosition, float yPosition, float rotation);

		void AddComponentToRender(GameObjectComponent* componentToAdd);

		void EraseEmptyComponents();


	private:

		//elements
		//render component only needs to call the render functions of the renderable components, so it can have const pointer to const objects
		std::vector<GameObjectComponent*> m_ComponentPointersVector;



    };
}

