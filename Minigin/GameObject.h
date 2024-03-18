#include <memory>
#include <vector>
#include "EngineMacros.h"

#ifndef GAMEOBJECT_HEADER
#define GAMEOBJECT_HEADER

namespace Engine
{
	class Texture2D;
	class Font;

	class GameObjectComponent;

	class TextComponent;
	class TransformComponent;
	class RenderComponent;
	class RotatorComponent;

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
		void RenderUI();

		//all game objects will have a transform component, so they all can have a set position method.
		void SetLocalPosition(float x, float y);
		void SetLocalRotation(float rotation);

		//set parent
		void SetParent(GameObject* parent);

		//get parent, children
		GameObject* const GetParent();
		int GetChildCount();
		GameObject* const GetChildAt(int index);

		//add a component
		void AddTexture2DComponent(const std::string& name, Texture2D* texturePointer = nullptr);
	
		void AddTextComponent(const std::string& name, Font* fontPointer = nullptr, const std::string& textString = "");

		void AddFPSComponent(GameObjectComponent* textComponentPointer = nullptr);

		void AddRotatorComponent(const std::string& name, float angularVelocity = 0.5f, float orbitRadius = 40.f);

		//remove all components with this name,with caveat that there should only be one component with a specific name on any given object?
		void RemoveComponentWithName(const std::string& componentName); 

		//remove all components of this type
		void RemoveAllComponentsOfType(COMPONENT_TYPE componentType);

		//Checks for the presence of a component with a certain name
		bool CheckForComponentWithName(std::string componentName) const; 

		//Checks for the presence of a component of a certain type
		bool CheckForComponentOfType(COMPONENT_TYPE componentType) const;


		//Get a pointer to a component by name
		GameObjectComponent* const GetComponentByName(const std::string& componentName) const;
		GameObjectComponent* const GetComponentByType(COMPONENT_TYPE componentType) const;

		TransformComponent* const GetTransformComponent() const;



	private:

		//functions
		bool HasThisChildOrGrandchild(const GameObject* const object);

		void RemoveChild(GameObject* const child);
		void AddChild(GameObject* const child);



		//elements
		
		//component types that an object does not need multiple of
		static const COMPONENT_TYPE m_DefaultComponents[];


		//components that every game object must have
		std::unique_ptr<TransformComponent> m_TransformComponentPointer;
		std::unique_ptr<RenderComponent>  m_RenderComponentPointer;





		//vector of extra components
		std::vector<std::unique_ptr<GameObjectComponent>> m_GameObjectComponentsVector; 
		int m_ExtraComponentCount{ 0 };


		//elements for hierarchical relationship with other game objects
		GameObject* m_ParentPointer{ nullptr };
		std::vector<GameObject*> m_ChildrenPointerVector;


		//dirty flags
		bool m_NeedsToBeDestroyed{ false };
		bool m_ParentTransformWasUpdated{ false };
		bool m_ParentWasChanged{ false };

	};
}

#endif