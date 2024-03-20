
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
	const std::string COMPONENT_TYPENAME_ORBIT{ "Orbit" };
	const std::string COMPONENT_TYPENAME_CACHETRASHER{ "CacheTrasher" };
	const std::string COMPONENT_TYPENAME_LOCOMOTION{ "Locomotion" };
	const std::string COMPONENT_TYPENAME_ANIMATEDTEXTURE2D{ "AnimatedTexture2D" };
	const std::string COMPONENT_TYPENAME_HEALTH{ "Health" };


	//component type enum
	enum class COMPONENT_TYPE
	{
		TextComponent,
		Texture2DComponent,
		TransformComponent,
		FPSComponent,
		RenderComponent,
		OrbitComponent,
		CacheTrasher,
		LocomotionComponent,
		AnimatedTexture2DComponent,
		HealthComponent
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



	enum struct XINPUT_CONTROLLER_BUTTON
	{
		DpadUp = 0x0001,
		DpadDown = 0x0002,
		DpadLeft = 0x0004,
		DpadRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		//Left_Thumb = 0x0040,
		//Right_Thumb = 0x0080,
		//Left_Shoulder = 0x0100,
		//Right_Shoulder = 0x0200,
		A = 0x1000,
		B = 0x2000,
		X = 0x4000,
		Y = 0x8000
	};

	enum struct XINPUT_CONTROLLER_BUTTON_STATE
	{
		IsDown = 0,
		IsUp = 1,
		WasPressed = 2,
		WasReleased = 3
	};

}

#endif