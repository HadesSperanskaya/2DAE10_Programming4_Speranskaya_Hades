#ifndef COMMAND_BASE_HEADER
#define COMMAND_BASE_HEADER

namespace Engine
{
	class GameObject;

	class Command
	{
	public:
		virtual ~Command() {};
		virtual void Execute(GameObject& actor) = 0;
	};


	class NullCommand : public Command
	{
	public:
		void Execute(GameObject& actor) { actor; };
	};
}

#endif