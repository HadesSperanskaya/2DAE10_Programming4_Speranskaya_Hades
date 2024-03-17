#pragma once
#include <vector>
#include <string>
#include <memory>

namespace Engine
{
	class GameObject;

	class Scene final
	{
		
	public:
		//functions

		//constructor
		Scene() = default;
		//destructor
		~Scene();
		//deleted 
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;


		void Add(GameObject* object);
		void Remove(GameObject* object);
		void RemoveAll();


		void Update(float deltaTime);
		void Render() const;
		void RenderUI();

		

	private: 
		
		//elements
		std::vector<GameObject*> m_Objects{};

	};

}
