#include "EventSetOne.h"

#include "GameObject.h"


#include "HealthComponent.h"
#include "UITextComponent.h"
#include "ScoreTrackerComponent.h"

#include "SteamAchievements.h"

using namespace Engine;



void UpdateLifeTrackerUI::Execute(GameObject* observer, GameObject* subject, GAME_EVENT passedEvent)
{
	if (passedEvent == GAME_EVENT::ENTITY_LOST_LIFE)
	{
		std::string textToSet = std::to_string(static_cast<HealthComponent*>(subject->GetComponentByType(COMPONENT_TYPE::HealthComponent))->m_CurrentLives);

		(static_cast<UITextComponent*>(observer->GetComponentByType(COMPONENT_TYPE::UITextComponent)))->SetVariableText(textToSet);
		return;

	}
}


void UpdatePointTrackerUI::Execute(GameObject* observer, GameObject* subject, GAME_EVENT passedEvent)
{
	if (passedEvent == GAME_EVENT::ENTITY_GAINED_POINTS)
	{
		std::string textToSet = std::to_string(static_cast<ScoreTrackerComponent*>(subject->GetComponentByType(COMPONENT_TYPE::ScoreTrackerComponent))->GetScore());

		(static_cast<UITextComponent*>(observer->GetComponentByType(COMPONENT_TYPE::UITextComponent)))->SetVariableText(textToSet);
		return;

	}
}


void WinOneGameAchivement::Execute(GameObject* observer, GameObject* subject, GAME_EVENT passedEvent)
{

	observer;
	if (passedEvent == GAME_EVENT::ENTITY_GAINED_POINTS)
	{
		int score = static_cast<ScoreTrackerComponent*>(subject->GetComponentByType(COMPONENT_TYPE::ScoreTrackerComponent))->GetScore();

		if (score >= 500)
		{
			if (SteamAchievements::m_SteamAchievementsPointer != nullptr)
			{
				SteamAchievements::m_SteamAchievementsPointer->SetAchievement("ACH_WIN_ONE_GAME");
			}
		}

	}
}