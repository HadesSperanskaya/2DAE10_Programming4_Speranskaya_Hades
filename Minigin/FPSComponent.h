#pragma once
#include "GameObjectComponent.h"
#include "TextComponent.h"

namespace dae
{
	class FPSComponent : public GameObjectComponent
	{
	public:

		FPSComponent();
		FPSComponent(GameObjectComponent* connectedTextComponent);
		~FPSComponent() = default;


		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;


		void Update(float deltaTime);

		const std::string& GetFPS() const;

		void SetTextComponentPointer(GameObjectComponent* connectedTextComponent);



	private:

		std::string m_FPS;
		TextComponent* m_TextComponentPointer;
	};

}

