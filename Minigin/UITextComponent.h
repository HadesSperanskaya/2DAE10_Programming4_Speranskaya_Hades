#include <vector>
#include <memory>
#include <glm/glm.hpp>



#include "GameObjectComponent.h"
#include "Observer.h"

#ifndef COMPONENT_UI_TEXT_HEADER
#define COMPONENT_UI_TEXT_HEADER
namespace Engine
{
	struct Transform;
	class Font;
	class Texture2DComponent;
	class GameObject;

    class UITextComponent : public GameObjectComponent, public Observer
    {
	public:
		//constructor
		UITextComponent(GameObject* gameObjectParentPointer, const std::string& componentName, Font* fontPointer = nullptr, std::string textString = "");

		//destructor
		~UITextComponent() = default;

		//copy/assignment constructor and move functions
		UITextComponent(const UITextComponent& other) = delete;
		UITextComponent(UITextComponent&& other) = delete;
		UITextComponent& operator=(const UITextComponent& other) = delete;
		UITextComponent& operator=(UITextComponent&& other) = delete;


		virtual void OnNotify(GameObject* gameObject, GAME_EVENT event) override;

		virtual void Update();
		virtual void Render(const Transform& transform) const;

		void SetPosition(float x, float y);
		void SetRotation(float rotation);
		void SetFont(Font* fontSharedPointer);


	private:
		//explicitly deleted default constructor
		UITextComponent() = delete;
	
		void UpdateTextureOfTextComponent();


		//elements

		//the dirty flag for marking that something needs to happen in the update function
		bool m_NeedsUpdate{ false };

		const glm::vec4 m_Color{ 255,255,255,255 }; // only white text is supported now

		std::string m_TextString;

		std::string m_InitialString;

		std::unique_ptr<Texture2DComponent> m_TextureComponentUniquePointer;

		std::unique_ptr<Transform> m_TransformUniquePointer;

		Font* m_FontPointer;

    };
}

#endif