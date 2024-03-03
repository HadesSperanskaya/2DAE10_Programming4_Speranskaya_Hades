#include <regex>
#include "FPSComponent.h"


using namespace Engine;


FPSComponent::FPSComponent(GameObject* gameObjectParentPointer, std::weak_ptr<GameObjectComponent>  connectedTextComponent) :
	GameObjectComponent(COMPONENT_TYPE::FPSComponent, COMPONENT_TYPENAME_FPS, gameObjectParentPointer),
	m_FPSTotal{ 0 },
	m_CyclesRun{ 0 },
	m_UpdateFrequency{1},
	m_TimePassed{0},
	m_TextComponentPointer{}
{
	if (connectedTextComponent.expired() != true && std::shared_ptr<GameObjectComponent>(connectedTextComponent)->m_OwnerGameObjectPointer == gameObjectParentPointer)
	{
		m_TextComponentPointer = std::weak_ptr<TextComponent>(std::static_pointer_cast<TextComponent>(std::shared_ptr<GameObjectComponent>(connectedTextComponent)));

	}
}

void FPSComponent::Update(float deltaTime)
{
	
	const float oneSecond = 1.0f;
	const float framesPerSecond = oneSecond / deltaTime;

	m_FPSTotal = m_FPSTotal + framesPerSecond;

	++m_CyclesRun;

	m_TimePassed = m_TimePassed + deltaTime;

	if(m_TimePassed >= m_UpdateFrequency)
	{
		const float averageFPS = m_FPSTotal / m_CyclesRun;

		m_FPSTotal = 0;
		m_CyclesRun = 0;
		m_TimePassed = 0;

		if (m_TextComponentPointer.expired() != true)
		{
			const std::string initialNumberConversion = std::to_string(averageFPS);

			std::smatch match{};

			std::regex_search(initialNumberConversion, match, std::regex{ "[[:d:]]*.[[:d:]][[:d:]]" });

			std::string outputString = match[0].str() + " FPS";

			std::shared_ptr<TextComponent>(m_TextComponentPointer)->SetText(outputString);

		}


	}


}


void FPSComponent::SetTextComponentPointer(std::weak_ptr<GameObjectComponent> textComponent)
{
	if (textComponent.expired() != true && std::shared_ptr<GameObjectComponent>(textComponent)->m_OwnerGameObjectPointer == m_OwnerGameObjectPointer)
	{
		m_TextComponentPointer = std::weak_ptr<TextComponent>(std::static_pointer_cast<TextComponent>(std::shared_ptr<GameObjectComponent>(textComponent)));

	}
}
