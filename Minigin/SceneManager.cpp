#include "SceneManager.h"
#include "Scene.h"



//void Engine::SceneManager::FixedUpdate(float fixedTimeStepTime)
//{
//	for (auto& scene : m_scenes)
//	{
//		scene->FixedUpdate(fixedTimeStepTime);
//	}
//}


Engine::SceneManager::~SceneManager()
{
	m_scenes.clear();
}

void Engine::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}
}




void Engine::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
		scene->RenderUI();
	}
}

Engine::Scene& Engine::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
