#include <stdexcept>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "TextComponent.h"
#include "Font.h"
#include "Texture2D.h"


//text component that has nothing yet
dae::TextComponent::TextComponent(std::string componentName)
	:
	GameObjectComponent(COMPONENT_TYPENAME_TEXT, componentName),
	m_NeedsUpdate{ false },
	m_FontSharedPointer{},
	m_TextureComponentUniquePointer{},
	m_TextString{}
{
	m_TextureComponentUniquePointer = std::unique_ptr<Texture2DComponent>(new Texture2DComponent{ componentName + COMPONENT_TYPENAME_TEXTURE2D });
	m_TransformComponentUniquePointer = std::unique_ptr<TransformComponent>(new TransformComponent{});
	SetRenderable(true);

};

//text component that has a font but not a text yet
dae::TextComponent::TextComponent(std::string componentName, std::shared_ptr<Font> fontSharedPointer)
	:
	GameObjectComponent(COMPONENT_TYPENAME_TEXT, componentName),
	m_NeedsUpdate{ false },
	m_FontSharedPointer{ fontSharedPointer },
	m_TextureComponentUniquePointer{},
	m_TextString{}

{
	m_TextureComponentUniquePointer = std::unique_ptr<Texture2DComponent>(new Texture2DComponent{ componentName + COMPONENT_TYPENAME_TEXTURE2D });
	m_TransformComponentUniquePointer = std::unique_ptr<TransformComponent>(new TransformComponent{});
	SetRenderable(true);



};

//tect component that has a font and a text 
dae::TextComponent::TextComponent(std::string componentName, std::shared_ptr<Font> fontSharedPointer, std::string textString)
	:
	GameObjectComponent(COMPONENT_TYPENAME_TEXT, componentName),
	m_NeedsUpdate{ false },
	m_FontSharedPointer{ fontSharedPointer },
	m_TextureComponentUniquePointer{},
	m_TextString{ textString }

{

	m_TextureComponentUniquePointer = std::unique_ptr<Texture2DComponent>(new Texture2DComponent{ componentName + COMPONENT_TYPENAME_TEXTURE2D });
	m_TransformComponentUniquePointer = std::unique_ptr<TransformComponent>(new TransformComponent{});

	UpdateTextureOfTextComponent();

	SetRenderable(true);
};



void dae::TextComponent::Update(float deltaTime)
{
	deltaTime; 

	if (m_NeedsUpdate)
	{
		UpdateTextureOfTextComponent();
	}
};

void dae::TextComponent::Render(float x, float y) const
{
	//get game object position
	const glm::vec3 position = m_TransformComponentUniquePointer->GetPosition();

	//render game object texture using game object position + position of the text object (world transform + object local transform)
	m_TextureComponentUniquePointer->Render(position.x + x, position.y + y);

};

void dae::TextComponent::SetText(const std::string& text)
{
	m_TextString = text;
	m_NeedsUpdate = true;
};

void dae::TextComponent::SetPosition(float x, float y)
{
	const float zeroZPosition = 0.00f;
	m_TransformComponentUniquePointer->SetPosition(x, y, zeroZPosition);
};

void dae::TextComponent::SetFont(std::shared_ptr<dae::Font> fontSharedPointer)
{
	m_FontSharedPointer.reset();
	m_FontSharedPointer = fontSharedPointer;
	m_NeedsUpdate = true;

};


void dae::TextComponent::UpdateTextureOfTextComponent()
{
	const SDL_Color color = { 255,255,255,255 }; // only white text is supported now

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

	m_TextureComponentUniquePointer.get()->SetTexture(std::make_shared<Texture2D>(texture));

	m_NeedsUpdate = false;


};
