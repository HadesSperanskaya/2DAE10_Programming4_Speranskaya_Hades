#pragma once
#include "GameObjectComponent.h"

#include "Texture2DComponent.h"
#include "TransformComponent.h"
#include "Font.h"

namespace Engine
{
	class Font;

    class TextComponent final : public GameObjectComponent
    {
	public:

		//constructors
		TextComponent(GameObject* gameObjectParentPointer, const std::string& componentName, Font* fontPointer = nullptr, std::string textString = "", const glm::vec4& color = { 255,255,255,255 });

		//destructor
		~TextComponent() = default;

		//copy and move constructors and assignment operators
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;


		//functions
		void Update(float deltaTime);
		void Render(float xPosition, float yPosition, float rotation) const;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetFont(Font* fontSharedPointer);


	private:

		//functions
		void UpdateTextureOfTextComponent();


		//elements

		//the dirty flag for marking that something needs to happen in the update function
		bool m_NeedsUpdate;

		const glm::vec4 m_Color; // only white text is supported now

		std::string m_TextString;

		//since this component generates its own text texture, the texture is unique
		std::unique_ptr<Texture2DComponent> m_TextureComponentUniquePointer;

		//this component has its own local transform
		std::unique_ptr<TransformComponent> m_TransformComponentUniquePointer;

		//this component references a font resource that is not unique to it, so shared pointer
		Font* m_FontPointer;


    };
}

