#include <glm/glm.hpp>

#include "GameObjectComponent.h"
#include "Texture2DComponent.h"
#include "TransformComponent.h"


#ifndef COMPONENT_TEXT_HEADER
#define COMPONENT_TEXT_HEADER
namespace Engine
{
	class Font;
	class Texture2D;
	class GameObject;

    class TextComponent final : public GameObjectComponent
    {
	public:

		//constructors
		TextComponent(GameObject* gameObjectParentPointer, const std::string& componentName, Font* fontPointer = nullptr, std::string textString = "");

		//destructor
		~TextComponent() = default;

		//copy and move constructors and assignment operators
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;


		//functions
		virtual void Update();
		virtual void Render(const Transform& transform) const;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetRotation(float rotation);
		void SetFont(Font* fontSharedPointer);


	private:
		//explicitly deleted default constructor
		TextComponent() = delete;

		//functions
		void UpdateTextureOfTextComponent();


		//elements

		//the dirty flag for marking that something needs to happen in the update function
		bool m_NeedsUpdate{ false };

		const glm::vec4 m_Color{ 255,255,255,255 }; // only white text is supported now

		std::string m_TextString;

		//since this component generates its own text texture, the texture is unique
		std::unique_ptr<Texture2DComponent> m_TextureComponentUniquePointer;

		//this component has its own local transform
		Transform m_Transform;

		//this component references a font resource that is not unique to it, so shared pointer
		Font* m_FontPointer;


    };
}

#endif