#pragma once
#include "Command.h"

namespace Engine
{
	class MoveLeftCommand : public Command
	{
	public:
		void Execute(GameObject& actor);
	};

	class MoveRightCommand : public Command
	{
	public:
		void Execute(GameObject& actor);
	};

	class MoveDownCommand : public Command
	{
	public:
		void Execute(GameObject& actor);
	};
	class MoveUpCommand : public Command
	{
	public:
		void Execute(GameObject& actor);
	};

}
