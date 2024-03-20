#include "Subject.h"
#include "GameObject.h"

using namespace Engine;

void Subject::AddObserver(Observer* observer)
{
	if(observer)
	{
		m_ObserversPointers.push_back(observer);
		++m_NumberOfObservers;
	}
}

void Subject::RemoveObserver(Observer* observer)
{
	if (observer)
	{
		m_ObserversPointers.erase(std::remove_if(m_ObserversPointers.begin(), m_ObserversPointers.end(), [observer](Observer* element) {return element == observer; }), m_ObserversPointers.end());
		--m_NumberOfObservers;
	}
}


void Subject::NotifyObservers(GameObject* gameObject, GAME_EVENT event)
{
	if (m_NumberOfObservers > 0)
	{
		for (auto observer : m_ObserversPointers)
		{
			observer->OnNotify(gameObject, event);
		}
	}
}