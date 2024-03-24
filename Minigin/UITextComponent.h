#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "GameObjectComponent.h"

#ifndef COMPONENT_UI_TEXT_HEADER
#define COMPONENT_UI_TEXT_HEADER
namespace Engine
{
	struct Transform;
	class Font;
	class TextComponent;
	class GameObject;

    class UITextComponent : public GameObjectComponent
    {
	public:
		//constructor
		UITextComponent(GameObject* gameObjectParentPointer, const std::string& componentName, Font* fontPointer, const std::string& variableText, const std::string& invariableText);

		//destructor
		~UITextComponent() = default;

		//copy/assignment constructor and move functions
		UITextComponent(const UITextComponent& other) = delete;
		UITextComponent(UITextComponent&& other) = delete;
		UITextComponent& operator=(const UITextComponent& other) = delete;
		UITextComponent& operator=(UITextComponent&& other) = delete;

		virtual void Update();
		virtual void Render(const Transform& transform) const;

		void SetVariableText(const std::string& text);
		void SetPosition(float x, float y);
		void SetRotation(float rotation);
		void SetFont(Font* fontSharedPointer);

		std::string m_InvariableText;
		std::string m_VariableText{" "};



	private:
		//explicitly deleted default constructor
		UITextComponent() = delete;
	
		std::unique_ptr<TextComponent> m_TextComponentUniquePointer;


		//elements


    };
}

#endif