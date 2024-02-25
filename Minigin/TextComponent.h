#pragma once
#include "GameObjectComponent.h"

#include "Texture2DComponent.h"
#include "TransformComponent.h"
#include "Font.h"

namespace dae
{
	class Font;


    class TextComponent final : public GameObjectComponent
    {
	public:

		//constructors
		TextComponent(std::string componentName);
		TextComponent(std::string componentName, std::shared_ptr<Font> fontSharedPointer);
		TextComponent(std::string componentName, std::shared_ptr<Font> fontSharedPointer, std::string textString);

		//destructor
		~TextComponent() = default;

		//copy and move constructors and assignment operators
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;


		//functions
		void Update(float deltaTime);
		void Render(float x, float y) const;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetFont(std::shared_ptr<Font> fontSharedPointer);


	private:
		//functions
		void UpdateTextureOfTextComponent();


		//elements
		bool m_NeedsUpdate;

		std::string m_TextString;

		std::unique_ptr<Texture2DComponent> m_TextureComponentUniquePointer;

		std::unique_ptr<TransformComponent> m_TransformComponentUniquePointer;

		std::shared_ptr<Font> m_FontSharedPointer;


    };
}

