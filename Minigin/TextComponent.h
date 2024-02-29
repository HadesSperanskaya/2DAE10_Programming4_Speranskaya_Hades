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
		TextComponent(std::string componentName, std::shared_ptr<Font> fontSharedPointer = nullptr, std::string textString = "");

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
		void SetFont(std::shared_ptr<Font> fontSharedPointer);


	private:

		//functions
		void UpdateTextureOfTextComponent();


		//elements

		//the dirty flag for marking that something needs to happen in the update function
		bool m_NeedsUpdate;

		std::string m_TextString;

		//since this component generates its own text texture, the texture is unique
		std::unique_ptr<Texture2DComponent> m_TextureComponentUniquePointer;

		//this component has its own local transform, as it has a render component
		std::unique_ptr<TransformComponent> m_TransformComponentUniquePointer;

		//this component references a font resource that is not unique to it, so shared pointer
		std::shared_ptr<Font> m_FontSharedPointer;


    };
}

