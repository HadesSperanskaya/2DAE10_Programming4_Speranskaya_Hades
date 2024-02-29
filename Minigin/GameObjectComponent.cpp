#include <string>
#include "GameObjectComponent.h"


using namespace Engine;

GameObjectComponent::GameObjectComponent(COMPONENT_TYPE componentType, std::string componentName) :
	m_ComponentType(componentType),
	m_ComponentName(componentName)
{

};

void GameObjectComponent::Update(float deltaTime)
{
	//doing this so compiler does not give the unreferenced formal parameter error
	deltaTime;
};

void GameObjectComponent::Render(float x, float y, float rotation) const
{
	//doing this so compiler does not give the unreferenced formal parameter error
	x;
	y;
	rotation;
};

