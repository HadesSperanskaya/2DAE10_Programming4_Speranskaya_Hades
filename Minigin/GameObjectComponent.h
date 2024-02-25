#pragma once
#include <memory>
#include <string>

//including macros here so that all components will have access to them as well.
#include "EngineMacros.h"

namespace dae
{
	class GameObjectComponent
	{
	public:

		//constructor
		GameObjectComponent(std::string componentTypeName, std::string componentName);

		//destructor
		virtual ~GameObjectComponent() = default;

		//copy and move constructor and assignment operators
		GameObjectComponent(const GameObjectComponent& other) = delete;
		GameObjectComponent(GameObjectComponent&& other) = delete;
		GameObjectComponent& operator=(const GameObjectComponent& other) = delete;
		GameObjectComponent& operator=(GameObjectComponent&& other) = delete;


		//functions

		virtual void Update(float deltaTime);
		virtual void Render(float x, float y) const;

		const std::string& GetComponentTypeName() const;
		const std::string& GetComponentName() const;
		bool GetIsRenderable() const;

		void SetComponentName(const std::string& newName);
		void SetRenderable(bool isRenderable);




	private:
		//component type cannot change after consutruction, so it is const
		const std::string m_ComponentTypeName;

		//component unique name can be changed after construction, so it is not const
		std::string m_ComponentUniqueName;

		//variable that tracks whether a component has a render function that needs calling for it.
		bool m_IsRenderable;


	};
}

