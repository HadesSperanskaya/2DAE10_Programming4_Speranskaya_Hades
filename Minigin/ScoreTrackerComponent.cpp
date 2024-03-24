#include "ScoreTrackerComponent.h"
#include "GameObject.h"
#include "SubjectComponent.h"

using namespace Engine;
ScoreTrackerComponent::ScoreTrackerComponent(GameObject* gameObjectParentPointer) :
	GameObjectComponent(COMPONENT_TYPE::ScoreTrackerComponent, COMPONENT_TYPENAME_SCORETRACKER, gameObjectParentPointer)
{

}


void ScoreTrackerComponent::IncreaseScore(int increaseValue)
{
	m_Score += increaseValue;

	GameObjectComponent* subjectPointer{ m_OwnerGameObjectPointer->GetComponentByType(COMPONENT_TYPE::SubjectComponent) };

	if (subjectPointer)
	{
		(static_cast<SubjectComponent*>(subjectPointer))->NotifyObservers(m_OwnerGameObjectPointer, this, GAME_EVENT::ENTITY_GAINED_POINTS);
	}

}



void ScoreTrackerComponent::SetScore(int score)
{
	m_Score = score;

	GameObjectComponent* subjectPointer{ m_OwnerGameObjectPointer->GetComponentByType(COMPONENT_TYPE::SubjectComponent) };

	if (subjectPointer)
	{
		(static_cast<SubjectComponent*>(subjectPointer))->NotifyObservers(m_OwnerGameObjectPointer, this, GAME_EVENT::ENTITY_GAINED_POINTS);
	}
}

int ScoreTrackerComponent::GetScore() const
{
	return m_Score;
}
