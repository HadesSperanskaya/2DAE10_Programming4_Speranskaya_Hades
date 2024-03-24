#include <stdexcept>
#include <SDL_ttf.h>

#include "ResourceOwner.h"
#include "Font.h"
#include "Texture2D.h"

#include "GameObject.h"

#include "UITextComponent.h"

#include "TextComponent.h"
#include "TransformComponent.h"

using namespace Engine;


UITextComponent::UITextComponent(GameObject* gameObjectParentPointer, const std::string& componentName, Font* fontPointer, const std::string& variableText, const std::string& invariableText)
	: GameObjectComponent(COMPONENT_TYPE::UITextComponent, componentName, gameObjectParentPointer),
	m_InvariableText{ invariableText },
	m_VariableText{variableText}
{

	m_TextComponentUniquePointer = std::make_unique<TextComponent>(gameObjectParentPointer, componentName, fontPointer, m_InvariableText + m_VariableText);

}


void UITextComponent::Update()
{
	m_TextComponentUniquePointer->Update();
};

void UITextComponent::SetVariableText(const std::string& text)
{
	m_VariableText = text;
	m_TextComponentUniquePointer->SetText(m_InvariableText + m_VariableText);
}

void UITextComponent::Render(const Transform& transform) const
{
	//sum.scale *= m_TransformUniquePointer->scale;

	m_TextComponentUniquePointer->Render(transform);

};

void UITextComponent::SetPosition(float x, float y)
{
	m_TextComponentUniquePointer->SetPosition(x, y);
};

void UITextComponent::SetRotation(float rotation)
{
	m_TextComponentUniquePointer->SetRotation(rotation);
};

void UITextComponent::SetFont(Font* fontSharedPointer)
{

	m_TextComponentUniquePointer->SetFont(fontSharedPointer);

};

