#include <algorithm>
#include "Scene.h"
#include "GameObject.h"


using namespace Engine;

void Scene::Add(GameObject* object)
{
	m_Objects.push_back(std::unique_ptr<GameObject>(object));
}

void Scene::Remove(GameObject* object)
{
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(),
								[object](const std::unique_ptr<GameObject>& element) { return (element.get() == object); }),
								m_Objects.end());
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void Scene::RenderUI()
{
	for (auto& object : m_Objects)
	{
		object->RenderUI();
	}
}
