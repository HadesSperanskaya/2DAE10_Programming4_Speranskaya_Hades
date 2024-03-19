#include <regex>

#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"

using namespace Engine;


FPSComponent::FPSComponent(GameObject* gameObjectParentPointer, TextComponent* connectedTextComponent) :
	GameObjectComponent(COMPONENT_TYPE::FPSComponent, COMPONENT_TYPENAME_FPS, gameObjectParentPointer)

{
	if (connectedTextComponent && connectedTextComponent->m_OwnerGameObjectPointer == gameObjectParentPointer)
	{
		m_TextComponentPointer = connectedTextComponent;

	}
}

void FPSComponent::Update()
{
	
	const float oneSecond = 1.0f;
	const float framesPerSecond = oneSecond / Scene::m_DeltaTime;

	m_FPSTotal = m_FPSTotal + framesPerSecond;

	++m_CyclesRun;

	m_TimePassed = m_TimePassed + Scene::m_DeltaTime;

	if(m_TimePassed >= m_UpdateFrequency)
	{
		const float averageFPS = m_FPSTotal / m_CyclesRun;

		m_FPSTotal = 0;
		m_CyclesRun = 0;
		m_TimePassed = 0;

		if (m_TextComponentPointer)
		{
			const std::string initialNumberConversion = std::to_string(averageFPS);

			std::smatch match{};

			std::regex_search(initialNumberConversion, match, std::regex{ "[[:d:]]*.[[:d:]][[:d:]]" });

			std::string outputString = match[0].str() + " FPS";

			m_TextComponentPointer->SetText(outputString);

		}


	}


}

void FPSComponent::SetTextComponentPointer(TextComponent* textComponent)
{
	if (textComponent  && textComponent->m_OwnerGameObjectPointer == m_OwnerGameObjectPointer)
	{
		m_TextComponentPointer = textComponent;

	}

}
