#include <vector>
#include "Observer.h"
#include "EngineMacros.h"

#ifndef SUBJECT_HEADER
#define SUBJECT_HEADER

namespace Engine
{
	class GameObject;

	class Subject
	{
	public:
		//functions
		Subject() = default;
		virtual ~Subject() = default;

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;


		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);


	protected:

		std::vector<Observer*> m_ObserversPointers;
		int m_NumberOfObservers{ 0 };

		virtual void NotifyObservers(GameObject* gameObject, GAME_EVENT event);


	};

}



#endif