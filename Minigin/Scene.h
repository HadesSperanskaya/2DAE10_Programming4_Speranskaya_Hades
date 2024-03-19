#include <vector>
#include <memory>

#ifndef SCENE_HEADER     
#define SCENE_HEADER

namespace Engine
{
	class GameObject;

	class Scene final
	{

	public:
	
		//constructor
		Scene();
		//destructor
		~Scene() = default;

		//deleted 
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;



		//functions
		void Add(GameObject* object); //add new object and assume ownership
		void Remove(GameObject* object); // destroy object
		void RemoveAll(); //destroy all objects


		void Update(float deltaTime);
		void Render() const;
		void RenderUI();
		
		static float m_DeltaTime;

	private:

		//elements
		static bool m_SceneCreated;

		std::vector<std::unique_ptr<GameObject>> m_ObjectPointers;


	};

}


#endif 






