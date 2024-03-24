#include "ScoreTrackerComponent.h"

using namespace Engine;
ScoreTrackerComponent::ScoreTrackerComponent(GameObject* gameObjectParentPointer) :
	GameObjectComponent(COMPONENT_TYPE::ScoreTrackerComponent, COMPONENT_TYPENAME_SCORETRACKER, gameObjectParentPointer)
{

}