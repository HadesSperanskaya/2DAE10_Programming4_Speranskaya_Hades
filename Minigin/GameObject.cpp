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


const std::string dae::GameObject::m_DefaultComponents[2]{COMPONENT_TYPENAME_TRANSFORM, COMPONENT_TYPENAME_RENDER };



dae::GameObject::GameObject()
{
	m_GameObjectComponentsVector.push_back(std::unique_ptr<GameObjectComponent>(new TransformComponent{}));
	m_GameObjectComponentsVector.push_back(std::unique_ptr<GameObjectComponent>(new RenderComponent{}));

	m_ComponentCount = int(m_GameObjectComponentsVector.size());
};


dae::GameObject::~GameObject()
{

	m_GameObjectComponentsVector.clear();

};

void dae::GameObject::FixedUpdate(float fixedTimeStepTime)
{
	fixedTimeStepTime;
	//not relevant for now
};

void dae::GameObject::Update(float deltaTime)
{

	for (int vectorIndex{ 0 }; vectorIndex < m_ComponentCount; ++vectorIndex)
	{
		m_GameObjectComponentsVector[vectorIndex]->Update(deltaTime);
	}
};

void dae::GameObject::Render() const
{
	//get game object position
	const glm::vec3 position = static_cast<TransformComponent*>(GetComponentByType(COMPONENT_TYPENAME_TRANSFORM))->GetPosition();

	//render using game object world position
	GetComponentByType(COMPONENT_TYPENAME_RENDER)->Render(position.x, position.y);
	

};


void dae::GameObject::SetPosition(float x, float y)
{
	(static_cast<TransformComponent*>(GetComponentByType(COMPONENT_TYPENAME_TRANSFORM)))->SetPosition(x, y, 0.0f);


};

void dae::GameObject::AddComponentPointerToRenderComponentByName(std::string name)
{
	static_cast<RenderComponent*>(GetComponentByType(COMPONENT_TYPENAME_RENDER))->AddComponentToRender(GetComponentByName(name));
}

void dae::GameObject::AddTexture2DComponent(std::string name)
{
	if (CheckForComponentOfType(COMPONENT_TYPENAME_TEXTURE2D))
	{
		return;
	}

	
	m_GameObjectComponentsVector.push_back(std::unique_ptr<GameObjectComponent>(static_cast<GameObjectComponent*>(new Texture2DComponent{ name })));

	++m_ComponentCount;
};

void dae::GameObject::AddTexture2DComponent(std::string name, std::shared_ptr<dae::Texture2D> textureSharedPointer)
{
	if (CheckForComponentOfType(COMPONENT_TYPENAME_TEXTURE2D))
	{
		return;
	}

	m_GameObjectComponentsVector.push_back(std::unique_ptr<GameObjectComponent>(static_cast<GameObjectComponent*>(new Texture2DComponent{ name, textureSharedPointer })));

	++m_ComponentCount;
};

void dae::GameObject::AddTextComponent(std::string name)
{

	if (CheckForComponentWithName(name))
	{
		return;
	}

	m_GameObjectComponentsVector.push_back(std::unique_ptr<GameObjectComponent>(static_cast<GameObjectComponent*>(new TextComponent{ name })));

	++m_ComponentCount;

};

void dae::GameObject::AddTextComponent(std::string name, std::shared_ptr<Font> fontSharedPointer)
{
	if (CheckForComponentWithName(name))
	{
		return;
	}

	m_GameObjectComponentsVector.push_back(std::unique_ptr<GameObjectComponent>(static_cast<GameObjectComponent*>(new TextComponent{ name, fontSharedPointer })));

	++m_ComponentCount;

};

void dae::GameObject::AddTextComponent(std::string name, std::shared_ptr<Font> fontSharedPointer, std::string textString)
{
	if (CheckForComponentWithName(name))
	{
		return;
	}

	m_GameObjectComponentsVector.push_back(std::unique_ptr<GameObjectComponent>(static_cast<GameObjectComponent*>(new TextComponent{ name, fontSharedPointer, textString })));

	++m_ComponentCount;
};

void dae::GameObject::AddFPSComponent()
{
	if (CheckForComponentWithName(COMPONENT_TYPENAME_FPS))
	{
		return;
	}

	m_GameObjectComponentsVector.push_back(std::unique_ptr<GameObjectComponent>(static_cast<GameObjectComponent*>(new FPSComponent{})));

	++m_ComponentCount;
}

void dae::GameObject::AddFPSComponent(GameObjectComponent* textComponentPointer)
{
	if (CheckForComponentWithName(COMPONENT_TYPENAME_FPS))
	{
		return;
	}

	m_GameObjectComponentsVector.push_back(std::unique_ptr<GameObjectComponent>(static_cast<GameObjectComponent*>(new FPSComponent{ textComponentPointer })));

	++m_ComponentCount;
}

void dae::GameObject::RemoveComponentWithName(std::string componentName)
{

	//find the component
	for (int vectorIndex{ 0 }; vectorIndex < m_ComponentCount; ++vectorIndex)
	{
		//once the component is found, check if it can be removed
		if (m_GameObjectComponentsVector[vectorIndex]->GetComponentName() == componentName)
		{
			const std::string typeOfComponentToRemove = m_GameObjectComponentsVector[vectorIndex]->GetComponentTypeName();

			for (auto forbiddenComponentType : m_DefaultComponents)
			{
				if (forbiddenComponentType == typeOfComponentToRemove)
				{
					return;
				}
			}

			//if the type was not a default type, erase the component

			m_GameObjectComponentsVector.erase(std::find(m_GameObjectComponentsVector.begin(), m_GameObjectComponentsVector.end(), m_GameObjectComponentsVector[vectorIndex]));
			--m_ComponentCount;

			return;
		}
	}


};

void dae::GameObject::RemoveAllComponentsOfType(std::string componentTypeName)
{
	//return if the desired deletion type is a default type
	for (auto forbiddenComponentType : m_DefaultComponents)
	{
		if (forbiddenComponentType == componentTypeName)
		{
			return;
		}
	}

	//find the components to delete and delete them
	for (int vectorIndex{ 0 }; vectorIndex < m_ComponentCount; ++vectorIndex)
	{
		//once the component is found, check if it can be removed
		if (m_GameObjectComponentsVector[vectorIndex]->GetComponentTypeName() == componentTypeName)
		{
			m_GameObjectComponentsVector.erase(std::find(m_GameObjectComponentsVector.begin(), m_GameObjectComponentsVector.end(), m_GameObjectComponentsVector[vectorIndex]));
			--m_ComponentCount;

		}
	}
};

bool dae::GameObject::CheckForComponentWithName(std::string componentName) const
{
	for (int vectorIndex{ 0 }; vectorIndex < m_ComponentCount; ++vectorIndex)
	{
		if (m_GameObjectComponentsVector[vectorIndex]->GetComponentName() == componentName)
		{
			return true;
		}
	}

	return false;
};

bool dae::GameObject::CheckForComponentOfType(std::string componentTypeName) const
{

	for (int vectorIndex{ 0 }; vectorIndex < m_ComponentCount; ++vectorIndex)
	{
		if (m_GameObjectComponentsVector[vectorIndex]->GetComponentTypeName() == componentTypeName)
		{
			return true;
		}
	}

	return false;

};

dae::GameObjectComponent* dae::GameObject::GetComponentByName(std::string componentName) const
{
	//figure out error handling for this later, involving checking for component


	for (int vectorIndex{ 0 }; vectorIndex < m_ComponentCount; ++vectorIndex)
	{
		if (m_GameObjectComponentsVector[vectorIndex]->GetComponentName() == componentName)
		{
			return m_GameObjectComponentsVector[vectorIndex].get();
		}
	}

	return nullptr;

};

dae::GameObjectComponent* dae::GameObject::GetComponentByType(std::string componentType) const
{
	//figure out error handling for this later, involving checking for component

	for (int vectorIndex{ 0 }; vectorIndex < m_ComponentCount; ++vectorIndex)
	{
		if (m_GameObjectComponentsVector[vectorIndex]->GetComponentTypeName() == componentType)
		{
			return m_GameObjectComponentsVector[vectorIndex].get();
		}
	}

	return nullptr;

};
