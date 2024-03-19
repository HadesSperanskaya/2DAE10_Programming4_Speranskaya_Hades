#include <memory>
#include <string>

#include "EngineMacros.h"

#ifndef GAMEOBJECT_COMPONENT_BASE_HEADER
#define GAMEOBJECT_COMPONENT_BASE_HEADER
namespace Engine
{
	class GameObject;
	struct Transform;

	class GameObjectComponent
	{
	public:

		//constructor
		GameObjectComponent(COMPONENT_TYPE componentType, const std::string& componentName, GameObject* gameObjectParentPointer);

		//destructor
		virtual ~GameObjectComponent() = default;

		//copy and move constructor and assignment operators
		GameObjectComponent(const GameObjectComponent& other) = delete;
		GameObjectComponent(GameObjectComponent&& other) = delete;
		GameObjectComponent& operator=(const GameObjectComponent& other) = delete;
		GameObjectComponent& operator=(GameObjectComponent&& other) = delete;


		//functions

		virtual void Update();

		//render function requires the parent game object's transform information to render the object in the correct place
		virtual void Render(const Transform& transform) const;
		virtual void RenderUI(const Transform& transform);


		//elements - public following the guideline "C.131: Avoid trivial getters and setters"

		//component parent object cannot change; components cannot be transferred between objects in my implementation.
		GameObject* const m_OwnerGameObjectPointer;

		//component type cannot change after construction, so it is const
		const COMPONENT_TYPE m_ComponentType;

		//component unique name, cannot be changed after construction
		const std::string m_ComponentName;


	private:
		//functions
		//explicitly deleted default constructor
		GameObjectComponent() = delete;

	};
}

#endif