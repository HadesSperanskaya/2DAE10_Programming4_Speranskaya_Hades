#pragma once

#include <memory>
#include "GameObjectComponent.h"

#ifndef COMPONENT_SCORETRACKER_HEADER
#define COMPONENT_SCORETRACKER_HEADER

namespace Engine
{
	class GameObject;

	class ScoreTrackerComponent final : public GameObjectComponent
	{
	public:

		//constructor
		ScoreTrackerComponent(GameObject* gameObjectParentPointer);

		//destructor
		~ScoreTrackerComponent() = default;

		//copy/assignment constructor and move functions
		ScoreTrackerComponent(const ScoreTrackerComponent& other) = delete;
		ScoreTrackerComponent(ScoreTrackerComponent&& other) = delete;
		ScoreTrackerComponent& operator=(const ScoreTrackerComponent& other) = delete;
		ScoreTrackerComponent& operator=(ScoreTrackerComponent&& other) = delete;

		void IncreaseScore(int increaseValue);
		void SetScore(int score);
		int GetScore() const;


	private:
		//explicitly deleted default constructor
		ScoreTrackerComponent() = delete;
		int m_Score{ 0 };



	};

}

#endif