#include "neo_bot.h"
#include <neo_gamerules.h>


void neo_bot_add()
{
	// Look at -count.
	int count = 1;
	count = clamp(count, 1, 16);

	int iTeam = -1;

	// Look at -frozen.
	bool bFrozen = false;

	// Ok, spawn all the bots.
	while (--count >= 0)
	{
		// We need to catch this fake client when it connects, but control escapes
		// to external engine code, so just kludging a status variable here for it.
		NEORules()->m_bNextClientIsFakeClient = true;

		BotPutInServer(bFrozen, iTeam);

		// Toggle this off after creating the bot
		NEORules()->m_bNextClientIsFakeClient = false;
	}
}

void neo_bot_kick()
{
	// Look at -count.
	int count = 1;
	count = clamp(count, 1, 16);

	int iTeam = -1;

	// Look at -frozen.
	bool bFrozen = false;

	// Ok, spawn all the bots.
	while (--count >= 0)
	{
		Msg("Failed to kick Bot.\n");
	}
}

ConCommand cc_Bot_Add("bot_add", neo_bot_add, "Add a bot. Alias for \"bot\".", FCVAR_CHEAT);
ConCommand cc_Bot_Kick("bot_kick", neo_bot_kick, "Kick a bot. Alias for \"bot\".", FCVAR_CHEAT);