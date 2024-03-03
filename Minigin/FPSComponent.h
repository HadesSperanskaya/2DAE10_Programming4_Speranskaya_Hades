#pragma once
#include "GameObjectComponent.h"
#include "TextComponent.h"

namespace Engine
{

	class TextComponent;

	class FPSComponent : public GameObjectComponent
	{
	public:

		//constructor
		FPSComponent(GameObject* gameObjectParentPointer, std::weak_ptr<GameObjectComponent> connectedTextComponent = std::weak_ptr<GameObjectComponent>{});

		//destructor
		~FPSComponent() = default;

		//constructors and movers
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;


		//functions
		void Update(float deltaTime);
		void SetTextComponentPointer(std::weak_ptr<GameObjectComponent> textComponent);



	private:
		//elements
		float m_CyclesRun;
		float m_FPSTotal;
		float m_TimePassed;
		float m_UpdateFrequency;
		std::weak_ptr<TextComponent> m_TextComponentPointer;
	};

}

