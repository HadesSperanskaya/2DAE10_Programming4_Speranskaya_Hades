#ifndef COMMAND_BASE_HEADER
#define COMMAND_BASE_HEADER

namespace Engine
{
	class GameObject;

	class Command
	{
	public:
		virtual ~Command() {};
		virtual void Execute(GameObject& actor);
		virtual void Execute();
	};


	class NullCommand : public Command
	{
	public:
		virtual void Execute(GameObject& actor) { actor; };
		virtual void Execute() {};
	};
}

#endif