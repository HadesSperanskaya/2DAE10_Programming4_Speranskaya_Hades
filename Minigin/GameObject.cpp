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

using namespace Engine;


const COMPONENT_TYPE GameObject::m_DefaultComponents[2]{COMPONENT_TYPE::TransformComponent, COMPONENT_TYPE::RenderComponent };



GameObject::GameObject():
	m_LocalTransformComponentUniquePointer{ std::unique_ptr<TransformComponent>(new TransformComponent{})},
	m_InheritedTransformComponentUniquePointer{ std::unique_ptr<TransformComponent>(new TransformComponent{})},
	m_RenderComponentUniquePointer{ std::unique_ptr<RenderComponent>(new RenderComponent{}) },
	m_ExtraComponentCount{0},
	m_ParentPointer{ std::weak_ptr<GameObject>{} }
{
	
};


GameObject::~GameObject()
{

	//if has a valid parent, remove itself from parent
	if (m_ParentPointer.expired() != false)
	{
		std::shared_ptr<GameObject>(m_ParentPointer)->RemoveChild(std::shared_ptr<GameObject>(this));
	}

	//if has children, default behaviour will be to destroy the children as well
	m_ChildrenPointerVector.clear();


	m_GameObjectComponentsVector.clear();



};


void GameObject::Update(float deltaTime)
{
	if (m_NeedsToUpdateWorldTransformInfo)
	{
		m_InheritedTransformComponentUniquePointer->m_Position = std::shared_ptr<GameObject>(m_ParentPointer)->m_LocalTransformComponentUniquePointer->m_Position;
		m_InheritedTransformComponentUniquePointer->m_Rotation = std::shared_ptr<GameObject>(m_ParentPointer)->m_LocalTransformComponentUniquePointer->m_Rotation;

		m_NeedsToUpdateWorldTransformInfo = false;
	}


	for (int vectorIndex{ 0 }; vectorIndex < m_ExtraComponentCount; ++vectorIndex)
	{
		m_GameObjectComponentsVector[vectorIndex]->Update(deltaTime);
	}
};

void GameObject::Render() const
{

	//render using game object world position
	m_RenderComponentUniquePointer->Render(m_InheritedTransformComponentUniquePointer->m_Position.x + m_LocalTransformComponentUniquePointer->m_Position.x,
											m_InheritedTransformComponentUniquePointer->m_Position.y + m_LocalTransformComponentUniquePointer->m_Position.y,
											m_InheritedTransformComponentUniquePointer->m_Rotation + m_LocalTransformComponentUniquePointer->m_Rotation);
	

};

void GameObject::SetPosition(float x, float y)
{
	m_LocalTransformComponentUniquePointer->m_Position.x = x;
	m_LocalTransformComponentUniquePointer->m_Position.y = y;

	//set all children as needing to have their world transform infos updated
	for (auto child : m_ChildrenPointerVector)
	{
		child->m_NeedsToUpdateWorldTransformInfo = true;
	}

};

void GameObject::SetRotation(float rotation)
{
	m_LocalTransformComponentUniquePointer->m_Rotation = rotation;
};

void GameObject::SetParent(std::weak_ptr<GameObject> parent)
{
	//if the parent is the same as this object, return
	if (std::shared_ptr<GameObject>(parent).get() == this)
	{
		return;
	}

	//return if to-be parent is already a child or grandchild or greatgranchild of this object
	if (HasThisChildOrGrandchild(parent))
	{
		return;
	}

	//if has a valid parent, remove itself from parent
	if (m_ParentPointer.expired() != false)
	{
		std::shared_ptr<GameObject>(parent)->RemoveChild(std::shared_ptr<GameObject>(this));
	}

	m_ParentPointer = parent;

	std::shared_ptr<GameObject>(m_ParentPointer)->AddChild(std::shared_ptr<GameObject>(this));

	m_NeedsToUpdateWorldTransformInfo = true;

}

std::weak_ptr<GameObject> GameObject::GetParent()
{
	return m_ParentPointer;
}

int GameObject::GetChildCount()
{
	return m_ChildrenPointerVector.size();
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
		m_GameObjectComponentsVector.push_back(std::static_pointer_cast<GameObjectComponent>(std::shared_ptr< Texture2DComponent>(new Texture2DComponent{ name, textureSharedPointer })));
	}
	else
	{
		m_GameObjectComponentsVector.push_back(std::static_pointer_cast<GameObjectComponent>(std::shared_ptr< Texture2DComponent>(new Texture2DComponent{ name })));

	}

	++m_ExtraComponentCount;

	m_RenderComponentUniquePointer->AddComponentToRender(m_GameObjectComponentsVector.back());
};



void GameObject::AddTextComponent(std::string name, std::shared_ptr<Font> fontSharedPointer, std::string textString)
{
	if (CheckForComponentWithName(name))
	{
		return;
	}

	m_GameObjectComponentsVector.push_back(std::static_pointer_cast<GameObjectComponent>(std::make_shared<TextComponent>(new TextComponent{ name, fontSharedPointer, textString })));

	++m_ExtraComponentCount;
	m_RenderComponentUniquePointer->AddComponentToRender(m_GameObjectComponentsVector.back());

};


void GameObject::AddFPSComponent(std::weak_ptr<GameObjectComponent> textComponentPointer)
{
	if (CheckForComponentOfType(COMPONENT_TYPE::FPSComponent))
	{
		return;
	}

	if (textComponentPointer.expired())
	{
		m_GameObjectComponentsVector.push_back(std::static_pointer_cast<GameObjectComponent>(std::shared_ptr <FPSComponent> (new FPSComponent{})));

	}
	else
	{
		m_GameObjectComponentsVector.push_back(std::static_pointer_cast<GameObjectComponent>(std::shared_ptr <FPSComponent>(new FPSComponent{ textComponentPointer })));

	}

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

	m_RenderComponentUniquePointer->EraseEmptyComponents();
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

	m_RenderComponentUniquePointer->EraseEmptyComponents();

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


bool GameObject::HasThisChildOrGrandchild(std::weak_ptr<GameObject> object)
{
	if(GetChildCount() > 0)
	{
		for (auto child : m_ChildrenPointerVector)
		{
			if (std::shared_ptr<GameObject>(object).get() == child.get())
			{
				return true;
			}
			if (child->GetChildCount() > 0)
			{
				if (std::shared_ptr<GameObject>(object).get()->HasThisChildOrGrandchild(object))
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
