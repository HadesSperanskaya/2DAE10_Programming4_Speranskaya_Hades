
#include "Renderer.h"
#include "AnimatedTexture2DComponent.h"
#include "Spritesheet.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Scene.h"

using namespace Engine;

float AnimatedTexture2DComponent::m_AnimationFrameRate = 0.05f; //12 frames per second - 0.05 seconds for each animation

AnimatedTexture2DComponent::AnimatedTexture2DComponent(GameObject* gameObjectParentPointer, const std::string& name, Spritesheet* texturePointer)
	:
	GameObjectComponent(COMPONENT_TYPE::Texture2DComponent, name, gameObjectParentPointer),
	m_SpritesheetTexturePointer{ texturePointer }
{

};


void AnimatedTexture2DComponent::Update()
{
	m_ElapsedTime = m_ElapsedTime + Scene::m_DeltaTime;

	if (m_ElapsedTime > m_AnimationFrameRate)
	{
		m_ElapsedTime = m_ElapsedTime - m_AnimationFrameRate;

		++m_CurrentFrame;

		m_CurrentFrame = m_CurrentFrame % m_SpritesheetTexturePointer->GetAnimationInformation(m_CurrentAnimationIndex)->frames;
	}

}


void AnimatedTexture2DComponent::SetCurrentAnimation(int animationIndex)
{
	m_CurrentAnimationIndex = animationIndex;
}


void AnimatedTexture2DComponent::Render(const Transform& transform) const
{

	if (m_SpritesheetTexturePointer)
	{
		Renderer::RenderSprite(m_SpritesheetTexturePointer, transform, m_CurrentAnimationIndex, m_CurrentAnimationIndex);
	}
}

