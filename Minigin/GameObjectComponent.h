#pragma once
#include <memory>
#include <string>

//including macros here so that all components will have access to them as well.
#include "EngineMacros.h"

namespace Engine
{
	class GameObjectComponent
	{
	public:

		//constructor
		GameObjectComponent(COMPONENT_TYPE componentType, std::string componentName);

		//destructor
		virtual ~GameObjectComponent() = default;

		//copy and move constructor and assignment operators
		GameObjectComponent(const GameObjectComponent& other) = delete;
		GameObjectComponent(GameObjectComponent&& other) = delete;
		GameObjectComponent& operator=(const GameObjectComponent& other) = delete;
		GameObjectComponent& operator=(GameObjectComponent&& other) = delete;


		//functions

		virtual void Update(float deltaTime);

		//render function requires the parent game object's transform information to render the object in the correct place
		virtual void Render(float xPosition, float yPosition, float rotation) const;


		//elements - public following the guideline "C.131: Avoid trivial getters and setters"

		//component type cannot change after consutruction, so it is const
		const COMPONENT_TYPE m_ComponentType;

		//component unique name can be changed after construction, so it is not const
		std::string m_ComponentName;




	private:
		

	};
}

