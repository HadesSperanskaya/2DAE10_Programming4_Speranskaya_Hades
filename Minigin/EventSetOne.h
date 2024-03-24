#include "Event.h"


#ifndef EVENT_SET_ONE_HEADER
#define EVENT_SET_ONE_HEADER



namespace Engine
{
	class GameObject;

	class UpdateLifeTrackerUI : public Event
	{
	public:
		virtual ~UpdateLifeTrackerUI() = default;
		virtual void Execute(GameObject* observer, GameObject* subject, GAME_EVENT passedEvent);
	};


	class UpdatePointTrackerUI : public Event
	{
	public:
		virtual ~UpdatePointTrackerUI() = default;
		virtual void Execute(GameObject* observer, GameObject* subject, GAME_EVENT passedEvent);
	};




}






#endif