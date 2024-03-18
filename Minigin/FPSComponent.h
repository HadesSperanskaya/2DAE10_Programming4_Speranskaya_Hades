#include "GameObjectComponent.h"


#ifndef COMPONENT_FPS_HEADER
#define COMPONENT_FPS_HEADER
namespace Engine
{

	class TextComponent;

	class FPSComponent final : public GameObjectComponent
	{
	public:

		//constructor
		explicit FPSComponent(GameObject* gameObjectParentPointer, TextComponent* connectedTextComponent);

		//destructor
		virtual ~FPSComponent() = default;

		//constructors and movers
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;


		//functions
		virtual void Update(float deltaTime);
		void SetTextComponentPointer(TextComponent* const textComponent);



	private:
		//functions
		FPSComponent() = delete;

		//elements
		float m_CyclesRun{0};
		float m_FPSTotal{0};
		float m_TimePassed{0};
		float m_UpdateFrequency;

		TextComponent* m_TextComponentPointer{nullptr};
	};

}

#endif