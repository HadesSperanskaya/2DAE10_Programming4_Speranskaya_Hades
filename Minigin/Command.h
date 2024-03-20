#ifndef COMMAND_BASE_HEADER
#define COMMAND_BASE_HEADER

namespace Engine
{
	class GameObject;

	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(GameObject& actor) = 0;
		virtual void Execute() = 0;
	};


	class NullCommand : public Command
	{
	public:
		virtual ~NullCommand() = default;

		virtual void Execute(GameObject& actor) { actor; };
		virtual void Execute() {};
	};
}

#endif