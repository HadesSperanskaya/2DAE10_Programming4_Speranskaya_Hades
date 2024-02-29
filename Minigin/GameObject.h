#pragma once
#include <memory>
#include <vector>


#include "GameObjectComponent.h"

namespace Engine
{
	class Texture2D;
	class Font;
	class TextComponent;
	class TransformComponent;
	class RenderComponent;

	class GameObject final
	{
	public:
		//Constructor
		GameObject();

		//Destructor
		~GameObject();

		//deleting copy constructor / move constructor / copy assignment / move assignment operators
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		//functions
		void Update(float deltaTime);
		void Render() const;

		//all game objects will have a transform component, so they all can have a set position method.
		void SetPosition(float x, float y);
		void SetRotation(float rotation);


		//add a component
		void AddTexture2DComponent(std::string name, std::shared_ptr<Texture2D> textureSharedPointer = nullptr);
	
		void AddTextComponent(std::string name, std::shared_ptr<Font> fontSharedPointer = nullptr, std::string textString = "");

		void AddFPSComponent(std::weak_ptr<GameObjectComponent> textComponentPointer = std::weak_ptr<GameObjectComponent>{});



		//remove all components with this name,with caveat that there should only be one component with a specific name on any given object?
		void RemoveComponentWithName(std::string componentName); 

		//remove all components of this type
		void RemoveAllComponentsOfType(COMPONENT_TYPE componentType);

		//Checks for the presence of a component with a certain name
		bool CheckForComponentWithName(std::string componentName) const; 

		//Checks for the presence of a component of a certain type
		bool CheckForComponentOfType(COMPONENT_TYPE componentType) const;


		//Get a pointer to a component by name
		std::weak_ptr<GameObjectComponent> GetComponentByName(std::string componentName) const; 
		std::weak_ptr<GameObjectComponent> GetComponentByType(COMPONENT_TYPE componentType) const;




	private:

		//component types that an object does not need multiple of
		static const COMPONENT_TYPE m_DefaultComponents[];

		std::unique_ptr<TransformComponent> m_TransformComponentUniquePointer;
		std::unique_ptr<RenderComponent> m_RenderComponentUniquePointer;

		//vector of extra components
		std::vector<std::shared_ptr<GameObjectComponent>> m_GameObjectComponentsVector; 


		int m_ExtraComponentCount;

	};
}
