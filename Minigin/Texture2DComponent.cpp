#include "Renderer.h"

#include "Texture2DComponent.h"
#include "Texture2D.h"


dae::Texture2DComponent::Texture2DComponent(const std::string& name)
	:
	GameObjectComponent(COMPONENT_TYPENAME_TEXTURE2D, name)
{

};



dae::Texture2DComponent::Texture2DComponent(const std::string& name, std::shared_ptr<dae::Texture2D> textureSharedPointer)
	:
	GameObjectComponent(COMPONENT_TYPENAME_TEXTURE2D, name)
{
	m_TextureSharedPointer = textureSharedPointer;

};

void dae::Texture2DComponent::Render(float x, float y) const
{
	if(m_TextureSharedPointer != nullptr)
	Renderer::GetInstance().RenderTexture(*m_TextureSharedPointer, x, y);
}


const std::shared_ptr<dae::Texture2D> dae::Texture2DComponent::GetTexture() const
{
	return m_TextureSharedPointer;
};


void dae::Texture2DComponent::SetTexture(std::shared_ptr<dae::Texture2D> textureSharedPointer)
{
	m_TextureSharedPointer = textureSharedPointer;
};

