#include "TransformComponent.h"
#include "GameObject.h"

using namespace Engine;

const Transform TransformComponent::m_WorldOrigin{};

TransformComponent::TransformComponent(GameObject* gameObjectParentPointer)
	:
	GameObjectComponent(COMPONENT_TYPE::TransformComponent, COMPONENT_TYPENAME_TRANSFORM, gameObjectParentPointer),
	m_World{&m_WorldOrigin}
{

};

void TransformComponent::UpdateDueToNewParentAssigned(GameObject* parent)
{
	if (parent)
	{
		m_World = &(parent->GetTransformComponent()->m_Combined);
	}
	else
	{
		m_World = &m_WorldOrigin;
	}


	//update position + rotation. scale currently not implemented
	switch (m_NewParentTransformInheritParameters.all)
	{
	case TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToWorld:

		//local transform is the offset from parent transform to current real transform
		m_Local.position = m_Combined.position - m_World->position;
		m_Local.rotation = m_Combined.rotation - m_World->rotation;

		//combined transform does not change


		break;

	case TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToParent:

		//local transform does not change
		
		//combined transform is new world plus the kept local
		m_Combined.position = m_Local.position + m_World->position;
		m_Combined.rotation = m_Local.rotation + m_World->rotation;

		break;

	case TRANSFORM_RELATIONSHIP_FlAG::CopyParent:

		//reset all locals to null
		m_Local.position = glm::vec2{ 0.f, 0.f};
		m_Local.rotation = 0;

		//combined just copies world transform
		m_Combined = *m_World;
		break;
	}
	
	
	

}


void TransformComponent::UpdateDueToParentBeingTransformed()
{

	//update position + rotation. scale currently not implemented
	switch (m_NewParentTransformInheritParameters.all)
	{
	case TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToWorld:

		//preserve combined, change local
		m_Local.position = m_Combined.position - m_World->position;
		m_Local.rotation = m_Combined.rotation - m_World->rotation;


		break;

	case TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToParent:
		//preserve local, change combined

		m_Combined.position = m_Local.position + m_World->position;
		m_Combined.rotation = m_Local.rotation + m_World->rotation;

		break;

	case TRANSFORM_RELATIONSHIP_FlAG::CopyParent:

		//reset locals
		m_Local.position = glm::vec2{ 0.f, 0.f};
		m_Local.rotation = 0;

		//change combined
		m_Combined = *m_World;

		break;
	}



}