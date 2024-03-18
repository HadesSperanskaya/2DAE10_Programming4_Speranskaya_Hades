
#include <string>

#ifndef ENGINE_MACROS_HEADER
#define ENGINE_MACROS_HEADER
namespace Engine
{
	const double PI_VALUE{ 3.1415926 };
	const double PI_TIMES_TW0_VALUE{ 6.2831853 };

	//component type name strings

	const std::string COMPONENT_TYPENAME_TEXT{ "Text" };
	const std::string COMPONENT_TYPENAME_TEXTURE2D{ "Texture2D" };
	const std::string COMPONENT_TYPENAME_TRANSFORM{ "Transform" };
	const std::string COMPONENT_TYPENAME_FPS{ "FPS" };
	const std::string COMPONENT_TYPENAME_RENDER{ "Render" };
	const std::string COMPONENT_TYPENAME_ROTATOR{ "Rotator" };
	const std::string COMPONENT_TYPENAME_CACHETRASHER{ "CacheTrasher" };


	//component type enum
	enum class COMPONENT_TYPE
	{
		TextComponent,
		Texture2DComponent,
		TransformComponent,
		FPSComponent,
		RenderComponent,
		RotatorComponent,
		CacheTrasher
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
		//potentially may expand to have the transform, rotate, and scale be separate
		TRANSFORM_RELATIONSHIP_FlAG all{ TRANSFORM_RELATIONSHIP_FlAG::PreserveCurrentRelativeToParent };
	};



}

#endif