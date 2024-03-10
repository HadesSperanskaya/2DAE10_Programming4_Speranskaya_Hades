#include <stdexcept>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "TextComponent.h"
#include "Font.h"
#include "Texture2D.h"

using namespace Engine;

TextComponent::TextComponent(GameObject* gameObjectParentPointer, const std::string& componentName, std::shared_ptr<Font> fontSharedPointer, std::string textString, const glm::vec4& color)
	:
	GameObjectComponent(COMPONENT_TYPE::TextComponent, componentName, gameObjectParentPointer),
	m_NeedsUpdate{ false },
	m_Color{ color },
	m_TextString{ textString },
	m_FontSharedPointer{ fontSharedPointer }

{

	m_TextureComponentUniquePointer = std::unique_ptr<Texture2DComponent>(new Texture2DComponent{ m_OwnerGameObjectPointer, componentName + COMPONENT_TYPENAME_TEXTURE2D });
	m_TransformComponentUniquePointer = std::unique_ptr<TransformComponent>(new TransformComponent{ m_OwnerGameObjectPointer });

	UpdateTextureOfTextComponent();

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

void TextComponent::SetFont(std::shared_ptr<Font> fontSharedPointer)
{
	m_FontSharedPointer.reset();
	m_FontSharedPointer = fontSharedPointer;
	//set the flag to dirty
	m_NeedsUpdate = true;

};


void TextComponent::UpdateTextureOfTextComponent()
{
	if (m_TextString.size() <= 0)
	{
		return;
	}


	const SDL_Color color = { Uint8(m_Color.r), Uint8(m_Color.b), Uint8(m_Color.g), Uint8(m_Color.a) }; // only white text is supported now

	const auto surf = TTF_RenderText_Blended(m_FontSharedPointer->GetFont(), m_TextString.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}

	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	
	SDL_FreeSurface(surf);

	(m_TextureComponentUniquePointer->m_TextureSharedPointer).reset();
	(m_TextureComponentUniquePointer->m_TextureSharedPointer) = std::make_shared<Texture2D>(texture);

	//clear the dirty flag
	m_NeedsUpdate = false;


};
