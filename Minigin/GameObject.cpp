#include <string>

#include "GameObject.h"

#include "EngineMacros.h"

#include "ResourceManager.h"
#include "Renderer.h"

#include "Texture2D.h"

#include "Texture2DComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RenderComponent.h"
#include "RotatorComponent.h"

using namespace Engine;


const COMPONENT_TYPE GameObject::m_DefaultComponents[2]{COMPONENT_TYPE::TransformComponent, COMPONENT_TYPE::RenderComponent };



GameObject::GameObject():
	m_LocalTransformComponentPointer{ std::shared_ptr<TransformComponent>(new TransformComponent{this})},
	m_WorldTransformComponentPointer{ std::shared_ptr<TransformComponent>(new TransformComponent{this}) },
	m_CombinedTransformComponentPointer{ std::shared_ptr<TransformComponent>(new TransformComponent{this}) },
	m_RenderComponentPointer{ std::unique_ptr<RenderComponent>(new RenderComponent{this}) },
	m_ExtraComponentCount{0},
	m_ParentPointer{ std::weak_ptr<GameObject>{} }
{
	
};


GameObject::~GameObject()
{

	//if has a valid parent, remove itself from parent
	if (m_ParentPointer.expired() != true)
	{
		std::shared_ptr<GameObject>(m_ParentPointer)->RemoveChild(std::shared_ptr<GameObject>(this));
	}

	//if has children, default behaviour will be to destroy the children as well
	m_ChildrenPointerVector.clear();


	m_GameObjectComponentsVector.clear();



};


void GameObject::Update(float deltaTime)
{
	if (m_ParentWasChanged) 
	{
		UpdateInheritedTransforms(m_TransformInheritanceParametersParentSwitch);

		m_ParentWasChanged = false;
	}

	if (m_ParentTransformWasUpdated)
	{
		m_WorldTransformComponentPointer->m_Position = std::shared_ptr<GameObject>(m_ParentPointer)->m_CombinedTransformComponentPointer->m_Position;
		m_WorldTransformComponentPointer->m_Rotation = std::shared_ptr<GameObject>(m_ParentPointer)->m_CombinedTransformComponentPointer->m_Rotation;

		m_ParentTransformWasUpdated = false;
	}


	m_CombinedTransformComponentPointer->m_Position = m_WorldTransformComponentPointer->m_Position + m_LocalTransformComponentPointer->m_Position;
	m_CombinedTransformComponentPointer->m_Rotation = m_WorldTransformComponentPointer->m_Rotation + m_LocalTransformComponentPointer->m_Rotation;



	for (int vectorIndex{ 0 }; vectorIndex < m_ExtraComponentCount; ++vectorIndex)
	{
		m_GameObjectComponentsVector[vectorIndex]->Update(deltaTime);
	}
};

void GameObject::Render() const
{

	//render using game object world position
	m_RenderComponentPointer->Render(m_CombinedTransformComponentPointer->m_Position.x,
									 m_CombinedTransformComponentPointer->m_Position.y,
									 m_CombinedTransformComponentPointer->m_Rotation);
	

};

void GameObject::SetPosition(float x, float y)
{
	m_LocalTransformComponentPointer->m_Position.x = x;
	m_LocalTransformComponentPointer->m_Position.y = y;

	m_CombinedTransformComponentPointer->m_Position = m_WorldTransformComponentPointer->m_Position + m_LocalTransformComponentPointer->m_Position;

	//set all children as needing to have their world transform infos updated
	for (auto child : m_ChildrenPointerVector)
	{
		child->m_ParentTransformWasUpdated = true;
	}

};

void GameObject::SetRotation(float rotation)
{
	m_LocalTransformComponentPointer->m_Rotation = rotation;

	m_CombinedTransformComponentPointer->m_Rotation = m_WorldTransformComponentPointer->m_Rotation + m_LocalTransformComponentPointer->m_Rotation;

	//set all children as needing to have their world transform infos updated
	for (auto child : m_ChildrenPointerVector)
	{
		child->m_ParentTransformWasUpdated = true;
	}

};

void GameObject::SetParent(std::weak_ptr<GameObject> parent)
{
	//if the parent is the same as this object, return 
	if (std::shared_ptr<GameObject>(parent) == shared_from_this())
	{
		return;
	}

	//return if to-be parent is already a child or grandchild or greatgranchild of this object
	if (HasThisChildOrGrandchild(parent))
	{
		return;
	}

	//if has a valid game object parent, remove itself from that parent
	if (!m_ParentPointer.expired())
	{
		std::shared_ptr<GameObject>(m_ParentPointer)->RemoveChild(shared_from_this());
	}

	//set new parent
	m_ParentPointer = parent;

	//add this object to the new parent.
	std::shared_ptr<GameObject>(m_ParentPointer)->AddChild(shared_from_this());

	m_ParentWasChanged = true;

}

std::weak_ptr<GameObject> GameObject::GetParent()
{
	return m_ParentPointer;
}

int GameObject::GetChildCount()
{
	return int(m_ChildrenPointerVector.size());
}

std::weak_ptr<GameObject> GameObject::GetChildAt(int index)
{
	return m_ChildrenPointerVector[index];
}

void GameObject::AddTexture2DComponent(std::string name, std::shared_ptr<Texture2D> textureSharedPointer)
{
	if (CheckForComponentOfType(COMPONENT_TYPE::Texture2DComponent))
	{
		return;
	}

	if(textureSharedPointer != nullptr)
	{
		m_GameObjectComponentsVector.push_back(std::static_pointer_cast<GameObjectComponent>(std::shared_ptr< Texture2DComponent>(new Texture2DComponent{ this, name, textureSharedPointer })));
	}
	else
	{
		m_GameObjectComponentsVector.push_back(std::static_pointer_cast<GameObjectComponent>(std::shared_ptr< Texture2DComponent>(new Texture2DComponent{ this, name })));

	}

	++m_ExtraComponentCount;

	m_RenderComponentPointer->AddComponentToRender(m_GameObjectComponentsVector.back());
};

void GameObject::AddTextComponent(std::string name, std::shared_ptr<Font> fontSharedPointer, std::string textString)
{
	if (CheckForComponentWithName(name))
	{
		return;
	}

	m_GameObjectComponentsVector.push_back(std::static_pointer_cast<GameObjectComponent>(std::shared_ptr<TextComponent>(new TextComponent{ this, name, fontSharedPointer, textString })));

	++m_ExtraComponentCount;
	m_RenderComponentPointer->AddComponentToRender(m_GameObjectComponentsVector.back());

};

void GameObject::AddFPSComponent(std::weak_ptr<GameObjectComponent> textComponentPointer)
{
	if (CheckForComponentOfType(COMPONENT_TYPE::FPSComponent))
	{
		return;
	}

	m_GameObjectComponentsVector.push_back(std::static_pointer_cast<GameObjectComponent>(std::shared_ptr <FPSComponent>(new FPSComponent{ this, textComponentPointer })));

	++m_ExtraComponentCount;
}

void GameObject::AddRotatorComponent(const std::string& name, float angularVelocity, float orbitRadius)
{
	if (CheckForComponentWithName(name))
	{
		return;
	}

	m_GameObjectComponentsVector.push_back(std::static_pointer_cast<GameObjectComponent>(std::shared_ptr<RotatorComponent>(new RotatorComponent{ this, name, angularVelocity, orbitRadius })));

	++m_ExtraComponentCount;
}

void GameObject::RemoveComponentWithName(std::string componentName)
{

	m_GameObjectComponentsVector.erase(std::remove_if(m_GameObjectComponentsVector.begin(), m_GameObjectComponentsVector.end(),
														[componentName](std::shared_ptr<GameObjectComponent> element)
														{
															return (element->m_ComponentName == componentName);
														}),
														m_GameObjectComponentsVector.end());

	m_RenderComponentPointer->EraseEmptyComponents();
};

void GameObject::RemoveAllComponentsOfType(COMPONENT_TYPE componentType)
{
	//return if the desired deletion type is a default type
	for (auto forbiddenComponentType : m_DefaultComponents)
	{
		if (forbiddenComponentType == componentType)
		{
			return;
		}
	}

	//find the components to delete and delete them
	m_GameObjectComponentsVector.erase(std::remove_if(m_GameObjectComponentsVector.begin(), m_GameObjectComponentsVector.end(),
														[componentType](std::shared_ptr<GameObjectComponent> element)
														{
															return (element->m_ComponentType == componentType);
														}), 
														m_GameObjectComponentsVector.end());

	m_RenderComponentPointer->EraseEmptyComponents();

};

bool GameObject::CheckForComponentWithName(std::string componentName) const
{

	for (const auto& component : m_GameObjectComponentsVector)
	{
		if (component->m_ComponentName == componentName)
		{
			return true;
		}
	}

	return false;
};

bool GameObject::CheckForComponentOfType(COMPONENT_TYPE componentType) const
{

	for (const auto& component : m_GameObjectComponentsVector)
	{
		if (component->m_ComponentType == componentType)
		{
			return true;
		}
	}

	return false;

};

std::weak_ptr<GameObjectComponent> GameObject::GetComponentByName(std::string componentName) const
{

	for (const auto& component : m_GameObjectComponentsVector)
	{
		if (component->m_ComponentName == componentName)
		{
			return std::weak_ptr<GameObjectComponent>(component);
		}
	}

	return std::weak_ptr<GameObjectComponent>{};

};

std::weak_ptr<GameObjectComponent> GameObject::GetComponentByType(COMPONENT_TYPE componentType) const
{

	for (const auto& component : m_GameObjectComponentsVector)
	{
		if (component->m_ComponentType == componentType)
		{
			return std::weak_ptr<GameObjectComponent>(component);
		}
	}

	return std::weak_ptr<GameObjectComponent>{};


};

std::weak_ptr<TransformComponent> GameObject::GetLocalTransformComponent() const
{
	return std::weak_ptr<TransformComponent>(m_LocalTransformComponentPointer);
}

std::weak_ptr<TransformComponent> GameObject::GetWorldTransformComponent() const
{
	return std::weak_ptr<TransformComponent>(m_WorldTransformComponentPointer);
}

std::weak_ptr<TransformComponent> GameObject::GetCombinedTransformComponent() const
{
	return std::weak_ptr<TransformComponent>(m_CombinedTransformComponentPointer);
}

bool GameObject::HasThisChildOrGrandchild(std::weak_ptr<GameObject> object)
{
	if(GetChildCount() > 0)
	{
		for (auto& child : m_ChildrenPointerVector)
		{
			if (std::shared_ptr<GameObject>(object) == child)
			{
				return true;
			}
			if (child->GetChildCount() > 0)
			{
				if (std::shared_ptr<GameObject>(object)->HasThisChildOrGrandchild(object))
				{
					return true;
				}
			}
		}
	}
	return false;
}

void GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
	m_ChildrenPointerVector.erase(std::remove_if(m_ChildrenPointerVector.begin(), m_ChildrenPointerVector.end(), [child](std::shared_ptr<GameObject> element) {return (element == child); }),
									m_ChildrenPointerVector.end());
}

void GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	m_ChildrenPointerVector.push_back(child);
}

void GameObject::UpdateInheritedTransforms(PARENT_CHILD_TRANSFORM_RELATIONSHIP parameters)
{

	if (m_ParentPointer.expired() != true)
	{

		//update position
		switch (parameters.Position)
		{
		case TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToWorld:

			//world position is parent position
			m_WorldTransformComponentPointer->m_Position = std::shared_ptr<GameObject>(m_ParentPointer)->m_CombinedTransformComponentPointer->m_Position;
			//local position is offset from parent position to current real position
			m_LocalTransformComponentPointer->m_Position = m_CombinedTransformComponentPointer->m_Position - m_WorldTransformComponentPointer->m_Position;
			//combined position does not change


			break;

		case TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToParent:

			//world position is parent position
			m_WorldTransformComponentPointer->m_Position = std::shared_ptr<GameObject>(m_ParentPointer)->m_CombinedTransformComponentPointer->m_Position;
			//local position does not change
			//combined position is new world plus the preserved local
			m_CombinedTransformComponentPointer->m_Position = m_LocalTransformComponentPointer->m_Position + m_WorldTransformComponentPointer->m_Position;

			break;

		case TRANSFORM_RELATIONSHIP_FlAG::CopyParent:

			//world position is parent position
			m_WorldTransformComponentPointer->m_Position = std::shared_ptr<GameObject>(m_ParentPointer)->m_CombinedTransformComponentPointer->m_Position;
			//local position reset to origin (aka parent)
			m_LocalTransformComponentPointer->m_Position = glm::vec3{ 0.f, 0.f, 0.f };
			//combined position is new world plus the preserved local
			m_CombinedTransformComponentPointer->m_Position = m_WorldTransformComponentPointer->m_Position;

			break;
		}


		//update rotation
		switch (parameters.Rotation)
		{
		case TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToWorld:

			//world rotation is parent rotation
			m_WorldTransformComponentPointer->m_Rotation = std::shared_ptr<GameObject>(m_ParentPointer)->m_CombinedTransformComponentPointer->m_Rotation;
			//local rotation is the offset from parent to current real 
			m_LocalTransformComponentPointer->m_Rotation = m_CombinedTransformComponentPointer->m_Rotation - m_WorldTransformComponentPointer->m_Rotation;
			//combined rotation does not change

			break;

		case TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToParent:

			//world rotation is parent rotation
			m_WorldTransformComponentPointer->m_Rotation = std::shared_ptr<GameObject>(m_ParentPointer)->m_CombinedTransformComponentPointer->m_Rotation;
			//local rotation does not change
			//combined rotation is new world plus the preserved local
			m_CombinedTransformComponentPointer->m_Rotation = m_LocalTransformComponentPointer->m_Rotation + m_WorldTransformComponentPointer->m_Rotation;

			break;

		case TRANSFORM_RELATIONSHIP_FlAG::CopyParent:
			
			//world rotation is parent rotation
			m_WorldTransformComponentPointer->m_Rotation = std::shared_ptr<GameObject>(m_ParentPointer)->m_CombinedTransformComponentPointer->m_Rotation;
			//local position reset to origin (aka parent)
			m_LocalTransformComponentPointer->m_Rotation = 0;
			//combined position is new world
			m_CombinedTransformComponentPointer->m_Rotation = m_WorldTransformComponentPointer->m_Rotation;

			break;
		}


	}
	else
	{
		//update position
		switch (parameters.Position)
		{
		case TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToWorld:

			//local is the offset from the scene origin. combined position does not change
			m_LocalTransformComponentPointer->m_Position = m_CombinedTransformComponentPointer->m_Position;
			//world is the scene origin
			m_WorldTransformComponentPointer->m_Position = glm::vec3{ 0.f, 0.f, 0.f };

			break;

		case TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToParent:

			//world is the scene origin
			m_WorldTransformComponentPointer->m_Position = glm::vec3{ 0.f, 0.f, 0.f };
			//local position does not change
			//combined position is just the preserved local
			m_CombinedTransformComponentPointer->m_Position = m_LocalTransformComponentPointer->m_Position;

			break;

		case TRANSFORM_RELATIONSHIP_FlAG::CopyParent:

			//fully move to scene origin
			m_WorldTransformComponentPointer->m_Position = glm::vec3{ 0.f, 0.f, 0.f };
			m_LocalTransformComponentPointer->m_Position = glm::vec3{ 0.f, 0.f, 0.f };
			m_CombinedTransformComponentPointer->m_Position = glm::vec3{ 0.f, 0.f, 0.f };

			break;
		}


		//update rotation
		switch (parameters.Rotation)
		{
		case TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToWorld:

			//set local rotation as total rotation
			m_LocalTransformComponentPointer->m_Rotation = m_CombinedTransformComponentPointer->m_Rotation;
			//world rotation is null
			m_WorldTransformComponentPointer->m_Rotation = 0;

			break;

		case TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToParent:

			//world rotation is null
			m_WorldTransformComponentPointer->m_Rotation = 0;
			//local rotation does not change
			//combined rotation is just the preserved local
			m_CombinedTransformComponentPointer->m_Rotation = m_LocalTransformComponentPointer->m_Rotation;

			break;

		case TRANSFORM_RELATIONSHIP_FlAG::CopyParent:

			//reset rotation to null
			m_WorldTransformComponentPointer->m_Rotation = 0;
			m_LocalTransformComponentPointer->m_Rotation = 0;
			m_CombinedTransformComponentPointer->m_Rotation = 0;

			break;
		}


	}
};
