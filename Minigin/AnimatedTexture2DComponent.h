
#include "GameObjectComponent.h"



#ifndef COMPONENT_ANIMATED_TEXTURE2D_COMPONENT_HEADER
#define COMPONENT_ANIMATED_TEXTURE2D_COMPONENT_HEADER

namespace Engine
{

	class GameObject;
	class Spritesheet;
	struct Transform;

	class AnimatedTexture2DComponent final : public GameObjectComponent
	{
	public:

		//constructor
		AnimatedTexture2DComponent(GameObject* gameObjectParentPointer, const std::string& name, Spritesheet* spriteSheetPointer);

		//destructor
		~AnimatedTexture2DComponent() = default;

		//copy/assignment constructor and move functions
		AnimatedTexture2DComponent(const AnimatedTexture2DComponent& other) = delete;
		AnimatedTexture2DComponent(AnimatedTexture2DComponent&& other) = delete;
		AnimatedTexture2DComponent& operator=(const AnimatedTexture2DComponent& other) = delete;
		AnimatedTexture2DComponent& operator=(AnimatedTexture2DComponent&& other) = delete;

		void Update();

		void Render(const Transform& transform) const;

		void SetCurrentAnimation(int animationIndex);

		//elements



	private:
		//explicitly deleted default constructor
		AnimatedTexture2DComponent() = delete;


		Spritesheet* m_SpritesheetTexturePointer;

		int m_CurrentAnimationIndex{ 0 };
		int m_CurrentFrame{ 0 };

		float m_ElapsedTime;

		static float m_AnimationFrameRate;
	};

}



#endif