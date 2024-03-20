#include <stdexcept>
#include <SDL_ttf.h>

#include "ResourceOwner.h"
#include "Font.h"
#include "Texture2D.h"

#include "GameObject.h"

#include "UITextComponent.h"

#include "Texture2DComponent.h"
#include "TransformComponent.h"
#include "HealthComponent.h"

using namespace Engine;


UITextComponent::UITextComponent(GameObject* gameObjectParentPointer, const std::string& componentName, Font* fontPointer, std::string textString)
	: GameObjectComponent(COMPONENT_TYPE::UITextComponent, componentName, gameObjectParentPointer),
	m_InitialString{textString},
	m_FontPointer{fontPointer}
{
	const SDL_Color colorConverted = { Uint8(m_Color.r), Uint8(m_Color.b), Uint8(m_Color.g), Uint8(m_Color.a) }; // only white text is supported now

	Texture2D* newTexture = ResourceOwner::CreateTexture2DFromText(colorConverted, m_FontPointer, m_TextString);

	m_TextureComponentUniquePointer = std::make_unique<Texture2DComponent>(m_OwnerGameObjectPointer, componentName + COMPONENT_TYPENAME_TEXTURE2D, newTexture);
	m_TransformUniquePointer = std::make_unique<Transform>();
}



void UITextComponent::OnNotify(GameObject* gameObject, GAME_EVENT event)
{

	switch (event)
	{
	case GAME_EVENT::ENTITY_DIED:


		break;


	case GAME_EVENT::ENTITY_LOST_LIFE:

		m_TextString = (m_InitialString + std::to_string(static_cast<HealthComponent*>(gameObject->GetComponentByType(COMPONENT_TYPE::HealthComponent))->m_CurrentLives));
		m_NeedsUpdate = true;


		break;
	}



}


void UITextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		UpdateTextureOfTextComponent();
	}
};

void UITextComponent::Render(const Transform& transform) const
{
	Transform sum = transform;
	sum.position += m_TransformUniquePointer->position;
	sum.rotation += m_TransformUniquePointer->rotation;
	//sum.scale *= m_TransformUniquePointer->scale;

	m_TextureComponentUniquePointer->Render(sum);

};

void UITextComponent::SetPosition(float x, float y)
{
	m_TransformUniquePointer->position = glm::vec2{ x, y };
};

void UITextComponent::SetRotation(float rotation)
{
	m_TransformUniquePointer->rotation = rotation;
};

void UITextComponent::SetFont(Font* fontSharedPointer)
{

	m_FontPointer = fontSharedPointer;
	//set the flag to dirty
	m_NeedsUpdate = true;

};


void UITextComponent::UpdateTextureOfTextComponent()
{
	if (m_TextString.size() <= 0)
	{
		m_TextureComponentUniquePointer->m_TexturePointer->ReplaceSDLTexture(nullptr);
		return;
	}


	const SDL_Color color = { Uint8(m_Color.r), Uint8(m_Color.b), Uint8(m_Color.g), Uint8(m_Color.a) }; // only white text is supported now


	SDL_Texture* newTexture = ResourceOwner::CreateSDLTextureFromText(color, m_FontPointer, m_TextString);

	if (newTexture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}

	m_TextureComponentUniquePointer->m_TexturePointer->ReplaceSDLTexture(newTexture);


	//clear the dirty flag
	m_NeedsUpdate = false;


};
