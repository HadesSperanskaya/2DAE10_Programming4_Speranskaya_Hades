
#include <glm/glm.hpp>

#include "Command.h"

#ifndef COMMANDSET_PLAYER_HEADER
#define COMMANDSET_PLAYER_HEADER
namespace Engine
{
	class GameObject;

	class MoveCommand : public Command
	{

	public:
		MoveCommand(const glm::vec2& movementDirection) { m_Direction = movementDirection; };

		virtual void Execute(GameObject& actor);
		virtual void Execute() {};


	private:

		glm::vec2 m_Direction{0, 0};

	};

	class TakeDamage : public Command
	{

	public:
		TakeDamage() {};

		virtual void Execute(GameObject& actor);
		virtual void Execute() {};


	private:

	};


	class GetPoints : public Command
	{

	public:
		GetPoints() {};

		virtual void Execute(GameObject& actor);
		virtual void Execute() {};


	private:

	};
}
#endif
