#include "GameObjectComponent.h"


#ifndef COMPONENT_FPS_HEADER
#define COMPONENT_FPS_HEADER
namespace Engine
{
	class GameObject;
	class TextComponent;

	class FPSComponent final : public GameObjectComponent
	{
	public:

		//constructor
		FPSComponent(GameObject* gameObjectParentPointer, TextComponent* connectedTextComponent);

		//destructor
		~FPSComponent() = default;

		//constructors and movers
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;


		//functions
		void Update();
		void SetTextComponentPointer(TextComponent* const textComponent);



	private:
		//explicitly deleted default constructor
		FPSComponent() = delete;


		//elements
		float m_CyclesRun{0};
		float m_FPSTotal{0};
		float m_TimePassed{0};
		const float m_UpdateFrequency{ 1 }; //every second, essentially

		TextComponent* m_TextComponentPointer{ nullptr };
	};

}

#endif