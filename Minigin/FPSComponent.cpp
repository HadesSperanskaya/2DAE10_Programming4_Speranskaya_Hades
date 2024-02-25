#include "FPSComponent.h"

dae::FPSComponent::FPSComponent() :
	GameObjectComponent(COMPONENT_TYPENAME_FPS, COMPONENT_TYPENAME_FPS),
	m_FPS{"0.0 FPS"},
	m_TextComponentPointer{nullptr}
{

}

dae::FPSComponent::FPSComponent(GameObjectComponent* connectedTextComponent) :
	GameObjectComponent(COMPONENT_TYPENAME_FPS, COMPONENT_TYPENAME_FPS),
	m_FPS{"0.0 FPS"},
	m_TextComponentPointer{ static_cast<TextComponent*>(connectedTextComponent) }
{

}

void dae::FPSComponent::Update(float deltaTime)
{
	const float oneSecond = 1.0f;

	const float framesPerSecond = oneSecond / deltaTime;

	m_FPS = std::to_string(framesPerSecond) + " FPS";

	m_TextComponentPointer->SetText(m_FPS);
}

const std::string& dae::FPSComponent::GetFPS() const
{
	return m_FPS;
}


void dae::FPSComponent::SetTextComponentPointer(GameObjectComponent* connectedTextComponent)
{
	m_TextComponentPointer = static_cast<TextComponent*>(connectedTextComponent);
}
