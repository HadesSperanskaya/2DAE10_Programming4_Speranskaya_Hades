#include "Renderer.h"

#include "Texture2DComponent.h"
#include "Texture2D.h"
#include "TransformComponent.h"


using namespace Engine;


Texture2DComponent::Texture2DComponent(GameObject* gameObjectParentPointer, const std::string& name, Texture2D* texturePointer)
	:
	GameObjectComponent(COMPONENT_TYPE::Texture2DComponent, name, gameObjectParentPointer),
	m_TexturePointer{ texturePointer }
{

};


void Texture2DComponent::Render(const Transform& transform) const
{

	//to do: implement rotation of texture. for not just stop it throwing error c4100 unreferenced formal parameter

	if (m_TexturePointer)
	{
		Renderer::RenderTexture(m_TexturePointer, transform.position.x, transform.position.y);
	}
}

