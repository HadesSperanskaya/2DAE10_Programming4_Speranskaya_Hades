#include "CommandsSetPlayer.h"
#include "GameObject.h"
#include "LocomotionComponent.h"
#include "EngineMacros.h"

using namespace Engine;


void MoveCommand::Execute(GameObject& actor)
{
	static_cast<LocomotionComponent*>(actor.GetComponentByType(COMPONENT_TYPE::LocomotionComponent))->AddVelocity(m_Direction);
}

