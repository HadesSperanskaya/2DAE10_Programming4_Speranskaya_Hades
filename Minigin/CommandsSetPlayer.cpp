#include "CommandsSetPlayer.h"
#include "GameObject.h"
#include "LocomotionComponent.h"
#include "HealthComponent.h"
#include "ScoreTrackerComponent.h"
#include "EngineMacros.h"

using namespace Engine;


void MoveCommand::Execute(GameObject& actor)
{
	static_cast<LocomotionComponent*>(actor.GetComponentByType(COMPONENT_TYPE::LocomotionComponent))->AddVelocity(m_Direction);
}


void TakeDamage::Execute(GameObject& actor)
{
	static_cast<HealthComponent*>(actor.GetComponentByType(COMPONENT_TYPE::HealthComponent))->TakeDamage(100);
}

void GetPoints::Execute(GameObject& actor)
{
	static_cast<ScoreTrackerComponent*>(actor.GetComponentByType(COMPONENT_TYPE::ScoreTrackerComponent))->m_Score += 20;;
}
