//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//
#ifndef NEO_BOT_BASE_H
#define NEO_BOT_BASE_H
#ifdef _WIN32
#pragma once
#endif

#include "cbase.h"
#include "convar.h"

#include <player.h>
#include <neo_player.h>

// If iTeam or iClass is -1, then a team or class is randomly chosen.
CBasePlayer *BotPutInServer( bool bFrozen, int iTeam );

void ClientPutInServer( edict_t *pEdict, const char *playername );
void Bot_Think(CNEO_Player* pBot);


#endif // NEO_BOT_BASE_H

