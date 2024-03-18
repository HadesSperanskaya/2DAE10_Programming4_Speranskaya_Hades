#include <stdexcept>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "Texture2DComponent.h"
#include "ResourceOwner.h"
#include "TransformComponent.h"

using namespace Engine;

TextComponent::TextComponent(GameObject* gameObjectParentPointer, const std::string& componentName, Font* fontPointer, std::string textString)
	:
	GameObjectComponent(COMPONENT_TYPE::TextComponent, componentName, gameObjectParentPointer),
	m_TextString{ textString },
	m_FontPointer{ fontPointer }

{
	const SDL_Color colorConverted = { Uint8(m_Color.r), Uint8(m_Color.b), Uint8(m_Color.g), Uint8(m_Color.a) }; // only white text is supported now

	Texture2D* newTexture = ResourceOwner::CreateTexture2DFromText(colorConverted, m_FontPointer, m_TextString);

	m_TextureComponentUniquePointer = std::make_unique<Texture2DComponent>(m_OwnerGameObjectPointer, componentName + COMPONENT_TYPENAME_TEXTURE2D, newTexture);
	m_TransformUniquePointer = std::make_unique<Transform>();


};



void TextComponent::Update(float deltaTime)
{
	deltaTime; 

	if (m_NeedsUpdate)
	{
		UpdateTextureOfTextComponent();
	}
};

void TextComponent::Render(const Transform& transform) const
{
	Transform sum = transform;
	sum.position += m_TransformUniquePointer->position;
	sum.rotation += m_TransformUniquePointer->rotation;
	//sum.scale *= m_TransformUniquePointer->scale;

	m_TextureComponentUniquePointer->Render(sum);

};

void TextComponent::SetText(const std::string& text)
{
	m_TextString = text;
	//set the dirty flag
	m_NeedsUpdate = true;
};

void TextComponent::SetPosition(float x, float y)
{
	const float zeroZPosition = 0.00f;
	m_TransformUniquePointer->position = glm::vec3{ x, y, zeroZPosition };
};

void TextComponent::SetRotation(float rotation)
{
	m_TransformUniquePointer->rotation = rotation;
};

void TextComponent::SetFont(Font* fontSharedPointer)
{

	m_FontPointer = fontSharedPointer;
	//set the flag to dirty
	m_NeedsUpdate = true;

};


void TextComponent::UpdateTextureOfTextComponent()
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
