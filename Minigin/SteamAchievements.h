#ifndef STEAM_ACHIEVEMENTS
#define STEAM_ACHIEVEMENTS

#include <memory>
#include "StatsAndAchievements.h"

namespace Engine
{
	class SteamAchievements final
	{
	public:

		// Achievement array which will hold data about the achievements and their state
		static Achievement_t m_Achievements[];
		// Global access to Achievements object
		static CSteamAchievements* m_SteamAchievementsPointer;
	};


}



#endif