#pragma once
#include <string>

namespace Engine
{
	//component type name strings

	const std::string COMPONENT_TYPENAME_TEXT{ "Text" };
	const std::string COMPONENT_TYPENAME_TEXTURE2D{ "Texture2D" };
	const std::string COMPONENT_TYPENAME_TRANSFORM{ "Transform" };
	const std::string COMPONENT_TYPENAME_FPS{ "FPS" };
	const std::string COMPONENT_TYPENAME_RENDER{ "RenderComponent" };


	//component type enum
	enum class COMPONENT_TYPE
	{
		TextComponent,
		Texture2DComponent,
		TransformComponent,
		FPSComponent,
		RenderComponent
	};

}