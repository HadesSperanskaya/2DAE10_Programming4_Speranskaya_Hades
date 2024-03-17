#include <stdexcept>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "TextComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "Minigin.h"
#include "ResourceManager.h"

using namespace Engine;

TextComponent::TextComponent(GameObject* gameObjectParentPointer, const std::string& componentName, Font* fontPointer, std::string textString, const glm::vec4& color)
	:
	GameObjectComponent(COMPONENT_TYPE::TextComponent, componentName, gameObjectParentPointer),
	m_NeedsUpdate{ false },
	m_Color{ color },
	m_TextString{ textString },
	m_FontPointer{ fontPointer }

{
	const SDL_Color colorConverted = { Uint8(m_Color.r), Uint8(m_Color.b), Uint8(m_Color.g), Uint8(m_Color.a) }; // only white text is supported now
	Texture2D* newTexture = ResourceManager::GetInstance().CreateTexture2DFromText(colorConverted, m_FontPointer, m_TextString);

	m_TextureComponentUniquePointer = std::unique_ptr<Texture2DComponent>(new Texture2DComponent{ m_OwnerGameObjectPointer, componentName + COMPONENT_TYPENAME_TEXTURE2D, newTexture });
	m_TransformComponentUniquePointer = std::unique_ptr<TransformComponent>(new TransformComponent{ m_OwnerGameObjectPointer });


};



void TextComponent::Update(float deltaTime)
{
	deltaTime; 

	if (m_NeedsUpdate)
	{
		UpdateTextureOfTextComponent();
	}
};

void TextComponent::Render(float xPosition, float yPosition, float rotation) const
{

	//render game object texture using game object position + position of the text object (world transform + object local transform)
	m_TextureComponentUniquePointer->Render(m_TransformComponentUniquePointer->m_Position.x + xPosition, 
												m_TransformComponentUniquePointer->m_Position.y + yPosition, 
												m_TransformComponentUniquePointer->m_Rotation + rotation);

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
	m_TransformComponentUniquePointer->m_Position = glm::vec3{ x, y, zeroZPosition };
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

	
	SDL_Texture* newTexture = ResourceManager::GetInstance().CreateSDLTextureFromText(color, m_FontPointer, m_TextString);

	if (newTexture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}

	m_TextureComponentUniquePointer->m_TexturePointer->ReplaceSDLTexture(newTexture);


	//clear the dirty flag
	m_NeedsUpdate = false;


};
