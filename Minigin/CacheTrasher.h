#pragma once
#include "GameObjectComponent.h"
#include "TextComponent.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl2.h"
#include <array>


namespace Engine
{
	struct Transform
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1 };
	};

	class GameObject3D
	{
	public:
		Transform transform;
		int ID;
	};

	class GameObject3DAlt
	{
	public:
		Transform* transform;
		int ID;
	};

	class CacheTrasher : public GameObjectComponent
	{

	public:

		//constructor
		CacheTrasher(GameObject* gameObjectParentPointer);

		//destructor
		~CacheTrasher() = default;

		//constructors and movers
		CacheTrasher(const CacheTrasher& other) = delete;
		CacheTrasher(CacheTrasher&& other) = delete;
		CacheTrasher& operator=(const CacheTrasher& other) = delete;
		CacheTrasher& operator=(CacheTrasher&& other) = delete;


		//functions
		void Update(float deltaTime);
		void RenderUI(float xPosition, float yPosition, float rotation);
		void RunExerciseOneCalculations();
		void RunExerciseTwoCalculations();


	private:

		//functions
		void ProccessRawData(const std::vector<float>& vectorOfRawData, float* outputTarget);


		//elements
		const int m_RepetitionsToDo{ 10 };
		bool m_UpdateExerciseOne{};
		bool m_UpdateExerciseTwo{};


		static const int m_ArraySize{ 9000000 };
		static const int m_StepCount{ 11 };

		std::array<int, m_ArraySize> m_ArrayOfIntegers;
		std::array<GameObject3D, m_ArraySize> m_ArrayOfGameObjects;
		std::array<GameObject3DAlt, m_ArraySize> m_ArrayOfAltGameObjects;

		float m_ExerciseOneOutput[m_StepCount];
		float m_ExerciseTwoPartOneOutput[m_StepCount];
		float m_ExerciseTwoPartTwoOutput[m_StepCount];

		
		
	};

}
