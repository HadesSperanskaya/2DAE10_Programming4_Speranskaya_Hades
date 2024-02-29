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
	m_TransformComponentUniquePointer{ std::unique_ptr<TransformComponent>(new TransformComponent{})},
	m_RenderComponentUniquePointer{ std::unique_ptr<RenderComponent>(new RenderComponent{}) },
	m_ExtraComponentCount{0}
{
	
};


GameObject::~GameObject()
{

	m_GameObjectComponentsVector.clear();

};


void GameObject::Update(float deltaTime)
{

	for (int vectorIndex{ 0 }; vectorIndex < m_ExtraComponentCount; ++vectorIndex)
	{
		m_GameObjectComponentsVector[vectorIndex]->Update(deltaTime);
	}
};

void GameObject::Render() const
{

	//render using game object world position
	m_RenderComponentUniquePointer->Render(m_TransformComponentUniquePointer->m_Position.x, m_TransformComponentUniquePointer->m_Position.y, m_TransformComponentUniquePointer->m_Rotation);
	

};

void GameObject::SetPosition(float x, float y)
{
	m_TransformComponentUniquePointer->m_Position.x = x;
	m_TransformComponentUniquePointer->m_Position.y = y;


};

void GameObject::SetRotation(float rotation)
{
	m_TransformComponentUniquePointer->m_Rotation = rotation;
};


void GameObject::AddTexture2DComponent(std::string name, std::shared_ptr<Texture2D> textureSharedPointer)
{
	if (CheckForComponentOfType(COMPONENT_TYPE::Texture2DComponent))
	{
		return;
	}

	if(textureSharedPointer != nullptr)
	{
		m_GameObjectComponentsVector.push_back(std::shared_ptr<GameObjectComponent>(static_cast<GameObjectComponent*>(new Texture2DComponent{ name, textureSharedPointer })));
	}
	else
	{
		m_GameObjectComponentsVector.push_back(std::shared_ptr<GameObjectComponent>(static_cast<GameObjectComponent*>(new Texture2DComponent{ name })));

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

	m_GameObjectComponentsVector.push_back(std::shared_ptr<GameObjectComponent>(static_cast<GameObjectComponent*>(new TextComponent{ name, fontSharedPointer, textString })));

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
		m_GameObjectComponentsVector.push_back(std::shared_ptr<GameObjectComponent>(static_cast<GameObjectComponent*>(new FPSComponent{})));

	}
	else
	{
		m_GameObjectComponentsVector.push_back(std::shared_ptr<GameObjectComponent>(static_cast<GameObjectComponent*>(new FPSComponent{ textComponentPointer })));

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
