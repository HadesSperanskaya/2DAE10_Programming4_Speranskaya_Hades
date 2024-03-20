#include <string>
#include <string>

#include "GameObject.h"

#include "EngineMacros.h"

#include "ResourceOwner.h"
#include "Renderer.h"

#include "Texture2D.h"
#include "Font.h"

#include "GameObjectComponent.h"

#include "Texture2DComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

#include "TextComponent.h"
#include "FPSComponent.h"
#include "OrbitComponent.h"
#include "LocomotionComponent.h"
#include "HealthComponent.h"
#include "UITextComponent.h"

using namespace Engine;


const COMPONENT_TYPE GameObject::m_DefaultComponents[2]{COMPONENT_TYPE::TransformComponent, COMPONENT_TYPE::RenderComponent };



GameObject::GameObject():
	m_TransformComponentPointer{ std::make_unique<TransformComponent>(this) },
	m_RenderComponentPointer{ std::make_unique<RenderComponent>(this) }
{
	
};


GameObject::~GameObject()
{
	//if has a valid parent, remove itself from parent
	if (m_ParentPointer)
	{
		m_ParentPointer->RemoveChild(this);
	}

	//if has children, remove itself from the children
	for (const auto& child : m_ChildrenPointerVector)
	{
		if (child)
		{
			child->SetParent(nullptr);
		}
	}


};


void GameObject::Update()
{
	if (m_ParentWasChanged) 
	{
		m_TransformComponentPointer->UpdateDueToNewParentAssigned(m_ParentPointer);

		m_ParentWasChanged = false;
	}

	if (m_ParentTransformWasUpdated)
	{
		m_TransformComponentPointer->UpdateDueToParentBeingTransformed();

		m_ParentTransformWasUpdated = false;
	}



	for (int vectorIndex{ 0 }; vectorIndex < m_ExtraComponentCount; ++vectorIndex)
	{
		m_GameObjectComponentsVector[vectorIndex]->Update();
	}
};

void GameObject::Render() const
{

	//render using game object world position
	m_RenderComponentPointer->Render(m_TransformComponentPointer->m_Combined);
	

};

void GameObject::RenderUI()
{

	//render using game object world position
	m_RenderComponentPointer->RenderUI(m_TransformComponentPointer->m_Combined);
	

};

//set local position
void GameObject::SetLocalPosition(float x, float y)
{

	m_TransformComponentPointer->m_Local.position = glm::vec2(x, y);

	m_TransformComponentPointer->m_Combined.position = m_TransformComponentPointer->m_Local.position + m_TransformComponentPointer->m_World->position;

	//set all children as needing to have their world transform infos updated
	for (auto child : m_ChildrenPointerVector)
	{
		child->m_ParentTransformWasUpdated = true;
	}

};

//set local rotation
void GameObject::SetLocalRotation(float rotation)
{
	m_TransformComponentPointer->m_Local.rotation = rotation;

	m_TransformComponentPointer->m_Combined.rotation = m_TransformComponentPointer->m_Local.rotation + m_TransformComponentPointer->m_World->rotation;

	//set all children as needing to have their world transform infos updated
	for (const auto& child : m_ChildrenPointerVector)
	{
		child->m_ParentTransformWasUpdated = true;
	}

};

void GameObject::SetParent(GameObject* parent)
{
	//if the parent is the same as this object, return 
	if (parent == this)
	{
		return;
	}

	//if the parent is already that object, also return
	if (parent == m_ParentPointer)
	{
		return;
	}


	//return if to-be parent is already a child or grandchild or greatgranchild of this object
	if (parent && HasThisChildOrGrandchild(parent))
	{
		return;
	}

	//if has a valid game object parent, remove itself from that parent
	if (m_ParentPointer)
	{
		m_ParentPointer->RemoveChild(this);
	}

	//set new parent
	m_ParentPointer = parent;

	//add this object to the new parent.
	if(m_ParentPointer)
	{
		m_ParentPointer->AddChild(this);
	}

	m_ParentWasChanged = true;

	m_TransformComponentPointer->UpdateDueToNewParentAssigned(m_ParentPointer);


}

GameObject* const GameObject::GetParent()
{
	return m_ParentPointer;
}

int GameObject::GetChildCount()
{
	return int(m_ChildrenPointerVector.size());
}

GameObject* const GameObject::GetChildAt(int index)
{
	return m_ChildrenPointerVector[index];
}

void GameObject::AddTexture2DComponent(const std::string& name, Texture2D* texturePointer)
{
	//can only add one texture to game object; components that have their own visuals msut have their own texture components to manage
	if (CheckForComponentOfType(COMPONENT_TYPE::Texture2DComponent))
	{
		return;
	}

	m_GameObjectComponentsVector.push_back(std::make_unique<Texture2DComponent>(this, name, texturePointer));

	++m_ExtraComponentCount;

	//give the render component the raw pointer to love and treasure and render;
	m_RenderComponentPointer->AddComponentToRender(m_GameObjectComponentsVector.back().get());
};

void GameObject::AddTextComponent(const std::string& name, Font* fontPointer, const std::string& textString)
{
	//type checking is a little cheaper, and an object is probably not going to have more than one text component added very often?
	if(CheckForComponentOfType(COMPONENT_TYPE::TextComponent))
	{
		if (CheckForComponentWithName(name))
		{
			return;
		}
	}

	m_GameObjectComponentsVector.push_back(std::make_unique<TextComponent>(this, name, fontPointer, textString));

	++m_ExtraComponentCount;

	//give the render component a raw pointer to love and treasure and render
	m_RenderComponentPointer->AddComponentToRender(m_GameObjectComponentsVector.back().get());

};

void GameObject::AddUITextComponent(const std::string& name, Font* fontPointer, const std::string& textString)
{
	//type checking is a little cheaper, and an object is probably not going to have more than one text component added very often?
	if(CheckForComponentOfType(COMPONENT_TYPE::UITextComponent))
	{
		if (CheckForComponentWithName(name))
		{
			return;
		}
	}

	m_GameObjectComponentsVector.push_back(std::make_unique<UITextComponent>(this, name, fontPointer, textString));

	++m_ExtraComponentCount;

	//give the render component a raw pointer to love and treasure and render
	m_RenderComponentPointer->AddComponentToRender(m_GameObjectComponentsVector.back().get());

};

void GameObject::AddFPSComponent(GameObjectComponent* textComponentPointer)
{
	//an object does not need more than one of these for sure. FPS component is rendered by a textcomponent that it knows about
	if (CheckForComponentOfType(COMPONENT_TYPE::FPSComponent))
	{
		return;
	}

	if(textComponentPointer->m_ComponentType == COMPONENT_TYPE::TextComponent)
	{
		m_GameObjectComponentsVector.push_back(std::make_unique<FPSComponent>(this, static_cast<TextComponent*>(textComponentPointer)));

		++m_ExtraComponentCount;
	}
}

void GameObject::AddOrbitComponent(const std::string& name)
{
	if (CheckForComponentWithName(name))
	{
		return;
	}

	m_GameObjectComponentsVector.push_back(std::make_unique<OrbitComponent>(this, name));

	++m_ExtraComponentCount;
}

void GameObject::AddLocomotionComponent(const std::string& name, float baseSpeed)
{
	if (CheckForComponentWithName(name))
	{
		return;
	}

	m_GameObjectComponentsVector.push_back(std::make_unique<LocomotionComponent>(this, name, baseSpeed));

	++m_ExtraComponentCount;
}

void GameObject::AddHealthComponent(int maxHealth, int maxLives)
{
	if (CheckForComponentOfType(COMPONENT_TYPE::HealthComponent))
	{
		return;
	}

	m_GameObjectComponentsVector.push_back(std::make_unique<HealthComponent>(this, maxHealth, maxLives));

	++m_ExtraComponentCount;
}


void GameObject::RemoveComponentWithName(const std::string& componentName)
{

	m_GameObjectComponentsVector.erase(std::remove_if(m_GameObjectComponentsVector.begin(), m_GameObjectComponentsVector.end(),
														[componentName](const std::unique_ptr<GameObjectComponent>& element)
														{
															return (element->m_ComponentName == componentName);
														}),
														m_GameObjectComponentsVector.end());

	m_RenderComponentPointer->EraseEmptyComponents();
};

void GameObject::RemoveAllComponentsOfType(COMPONENT_TYPE componentType)
{
	//return if the desired deletion type is a default type eg render, transform. do not even have to bother trying to remove them
	for (auto forbiddenComponentType : m_DefaultComponents)
	{
		if (forbiddenComponentType == componentType)
		{
			return;
		}
	}

	//find the components to delete and delete them
	m_GameObjectComponentsVector.erase(std::remove_if(m_GameObjectComponentsVector.begin(), m_GameObjectComponentsVector.end(),
														[componentType](const std::unique_ptr<GameObjectComponent>& element)
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

GameObjectComponent* GameObject::GetComponentByName(const std::string& componentName) const
{
	for (const auto& component : m_GameObjectComponentsVector)
	{
		if (component->m_ComponentName == componentName)
		{
			return component.get();
		}
	}

	return nullptr;
};

GameObjectComponent* GameObject::GetComponentByType(COMPONENT_TYPE componentType) const
{

	for (const auto& component : m_GameObjectComponentsVector)
	{
		if (component->m_ComponentType == componentType)
		{
			return component.get();
		}
	}
	
	return nullptr;
};

TransformComponent* const GameObject::GetTransformComponent() const
{
	return m_TransformComponentPointer.get();
}



bool GameObject::HasThisChildOrGrandchild(const GameObject* const object)
{
	if(GetChildCount() > 0)
	{
		for (auto& child : m_ChildrenPointerVector)
		{
			if (object == child)
			{
				return true;
			}
			if (child->GetChildCount() > 0)
			{
				if (child->HasThisChildOrGrandchild(object))
				{
					return true;
				}
			}
		}
	}
	return false;
}

void GameObject::RemoveChild(GameObject* const child)
{
	m_ChildrenPointerVector.erase(std::remove_if(m_ChildrenPointerVector.begin(), m_ChildrenPointerVector.end(), 
									[child](GameObject* const element) {return (element == child); }),
									m_ChildrenPointerVector.end());
}

void GameObject::AddChild(GameObject* const child)
{
	m_ChildrenPointerVector.push_back(child);
}

