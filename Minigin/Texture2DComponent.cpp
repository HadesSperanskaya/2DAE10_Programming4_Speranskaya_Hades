#include "Renderer.h"

#include "Texture2DComponent.h"
#include "Texture2D.h"


using namespace Engine;


Texture2DComponent::Texture2DComponent(const std::string& name, std::shared_ptr<Texture2D> textureSharedPointer)
	:
	GameObjectComponent(COMPONENT_TYPE::Texture2DComponent, name),
	m_TextureSharedPointer{ textureSharedPointer }
{

};


void Texture2DComponent::Render(float xPosition, float yPosition, float rotation) const
{

	//to do: implement rotation of texture. for not just stop it throwing error c4100 unreferenced formal parameter
	rotation;

	if (m_TextureSharedPointer != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_TextureSharedPointer, xPosition, yPosition);
	}
}

