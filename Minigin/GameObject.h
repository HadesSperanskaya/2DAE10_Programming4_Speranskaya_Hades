#pragma once
#include <memory>
#include <vector>


#include "GameObjectComponent.h"

namespace dae
{
	class Texture2D;
	class Font;
	class TextComponent;

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
		void FixedUpdate(float fixedTimeStepTime);
		void Update(float deltaTime);
		void Render() const;

		//all game objects will have a transform component, so they all can have a set position method.
		void SetPosition(float x, float y);
		void AddComponentPointerToRenderComponentByName(std::string name);

		//add a component
		

		void AddTexture2DComponent(std::string name);
		void AddTexture2DComponent(std::string name, std::shared_ptr<Texture2D> textureSharedPointer);
		void AddTextComponent(std::string name);
		void AddTextComponent(std::string name, std::shared_ptr<Font> fontSharedPointer);
		void AddTextComponent(std::string name, std::shared_ptr<Font> fontSharedPointer, std::string textString);
		void AddFPSComponent();
		void AddFPSComponent(GameObjectComponent* textComponentPointer);



		//remove all components with this name,with caveat that there should only be one component with a specific name on any given object?
		void RemoveComponentWithName(std::string componentName); 

		//remove all components of this type
		void RemoveAllComponentsOfType(std::string componentTypeName); 

		//Checks for the presence of a component with a certain name
		bool CheckForComponentWithName(std::string componentName) const; 

		//Checks for the presence of a component of a certain type
		bool CheckForComponentOfType(std::string componentTypeName) const; 


		//Get a pointer to a component by name
		GameObjectComponent* GetComponentByName(std::string componentName) const; 
		GameObjectComponent* GetComponentByType(std::string componentType) const; 




	private:

		//to store a list of all components that are always part of a game object, and that it can only have one of
		static const std::string m_DefaultComponents[];


		//vector storing the components. could potentially later change to an unordered set with a lambda that uses component name to check
		//that the new added component is
		std::vector<std::unique_ptr<GameObjectComponent>> m_GameObjectComponentsVector; 


		int m_ComponentCount;

	};
}
