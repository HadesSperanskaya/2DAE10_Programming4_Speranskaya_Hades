#include <algorithm>
#include "Scene.h"
#include "GameObject.h"


using namespace Engine;


float Scene::m_DeltaTime = 0;
bool Scene::m_SceneCreated = false;

Scene::Scene()
{
	if (m_SceneCreated == false)
	{
		m_SceneCreated = true;
	}
}

void Scene::Add(GameObject* object)
{
	m_ObjectPointers.push_back(std::unique_ptr<GameObject>(object));
}

void Scene::Remove(GameObject* object)
{
	m_ObjectPointers.erase(std::remove_if(m_ObjectPointers.begin(), m_ObjectPointers.end(),
											[object](const std::unique_ptr<GameObject>& element) { return (element.get() == object); }),
											m_ObjectPointers.end());
}

void Scene::RemoveAll()
{
	m_ObjectPointers.clear();
}

void Scene::Update(float deltaTime)
{
	m_DeltaTime = deltaTime;
	for(auto& object : m_ObjectPointers)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_ObjectPointers)
	{
		object->Render();
	}
}

void Scene::RenderUI()
{
	for (auto& object : m_ObjectPointers)
	{
		object->RenderUI();
	}
}
