#pragma once
#include <string>

namespace Engine
{
	const double PI_VALUE{ 3.1415926 };
	const double PI_TIMES_TW0_VALUE{ 6.2831853 };

	//component type name strings

	const std::string COMPONENT_TYPENAME_TEXT{ "Text" };
	const std::string COMPONENT_TYPENAME_TEXTURE2D{ "Texture2D" };
	const std::string COMPONENT_TYPENAME_TRANSFORM{ "Transform" };
	const std::string COMPONENT_TYPENAME_FPS{ "FPS" };
	const std::string COMPONENT_TYPENAME_RENDER{ "RenderComponent" };
	const std::string COMPONENT_TYPENAME_ROTATOR{ "RotatorComponent" };


	//component type enum
	enum class COMPONENT_TYPE
	{
		TextComponent,
		Texture2DComponent,
		TransformComponent,
		FPSComponent,
		RenderComponent,
		RotatorComponent
	};


	//flag types
	enum class TRANSFORM_RELATIONSHIP_FlAG
	{
		PreserveCurrentRelativeToWorld,
		PreserveCurrentRelativeToParent,
		CopyParent
	};

	//struct to hold info on how a child s
	struct PARENT_CHILD_TRANSFORM_RELATIONSHIP
	{
		TRANSFORM_RELATIONSHIP_FlAG Position{ TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToParent };
		TRANSFORM_RELATIONSHIP_FlAG Rotation{ TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToParent };
	};



}