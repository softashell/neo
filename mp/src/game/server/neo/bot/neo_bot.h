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


// If iTeam or iClass is -1, then a team or class is randomly chosen.
CBasePlayer *BotPutInServer( bool bFrozen, int iTeam );


#endif // NEO_BOT_BASE_H

