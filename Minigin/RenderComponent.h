#pragma once
#include "GameObjectComponent.h"
#include <vector>

namespace dae
{

	class Texture2DComponent;

    class RenderComponent : public GameObjectComponent
    {
	public: 
		//constructors
		RenderComponent();

		//destructor
		~RenderComponent() = default;

		//copy and move constructors and assignment operators
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;


		//functions
		void Render(float x, float y) const;

		void AddComponentToRender(GameObjectComponent* objectToRender);
		void RemoveComponentToRenderByName(const std::string& componentName);


	private:

		std::vector<GameObjectComponent*> m_ObjectsToRenderVector;



    };
}

