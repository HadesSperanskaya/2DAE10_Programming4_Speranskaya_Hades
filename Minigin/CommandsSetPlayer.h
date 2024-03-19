#include "Command.h"

#ifndef COMMANDSET_PLAYER_HEADER
#define COMMANDSET_PLAYER_HEADER
namespace Engine
{
	class MoveCommand : public Command
	{
	public:
		virtual void Execute(GameObject& actor);
	};


}
#endif
