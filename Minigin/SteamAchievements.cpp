#include "SteamAchievements.h"


using namespace Engine;


Achievement_t SteamAchievements::m_Achievements[] =
{
	_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
	_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
	_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
	_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
};

// Global access to Achievements object
CSteamAchievements* SteamAchievements::m_SteamAchievementsPointer = nullptr;