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

		void AddComponentToRender(std::shared_ptr<GameObjectComponent> componentToAdd);

		void EraseEmptyComponents();


	private:

		//elements
		std::vector<std::weak_ptr<GameObjectComponent>> m_ComponentWeakPointersVector;



    };
}

