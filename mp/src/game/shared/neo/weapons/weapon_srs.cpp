#include "cbase.h"
#include "weapon_srs.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_NETWORKCLASS_ALIASED(WeaponSRS, DT_WeaponSRS)

BEGIN_NETWORK_TABLE(CWeaponSRS, DT_WeaponSRS)
	DEFINE_NEO_BASE_WEP_NETWORK_TABLE
END_NETWORK_TABLE()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA(CWeaponSRS)
	DEFINE_NEO_BASE_WEP_PREDICTION
END_PREDICTION_DATA()
#endif

NEO_IMPLEMENT_ACTTABLE(CWeaponSRS)

LINK_ENTITY_TO_CLASS(weapon_srs, CWeaponSRS);

PRECACHE_WEAPON_REGISTER(weapon_srs);

CWeaponSRS::CWeaponSRS()
{
	m_flSoonestAttack = gpGlobals->curtime;
	m_flAccuracyPenalty = 0;

	m_nNumShotsFired = 0;
}

void CWeaponSRS::DryFire()
{
	WeaponSound(EMPTY);
	SendWeaponAnim(ACT_VM_DRYFIRE);

	m_flNextPrimaryAttack = gpGlobals->curtime + SequenceDuration();
}

void CWeaponSRS::Spawn()
{
	BaseClass::Spawn();
}

bool CWeaponSRS::Deploy(void)
{
	return BaseClass::Deploy();
}

void CWeaponSRS::PrimaryAttack(void)
{
	if (!ShootingIsPrevented() && GetRoundChambered()) {
		BaseClass::PrimaryAttack();
		if (m_flLastAttackTime == gpGlobals->curtime) {
			m_bRoundChambered = false;
		}
	}
}

void CWeaponSRS::UpdatePenaltyTime()
{
	auto owner = ToBasePlayer(GetOwner());

	if (!owner)
	{
		return;
	}

	if ((owner->m_nButtons & IN_ATTACK) == false)
	{
		if (m_flSoonestAttack < gpGlobals->curtime)
		{ 
			m_flAccuracyPenalty -= gpGlobals->frametime;
			m_flAccuracyPenalty = clamp(m_flAccuracyPenalty, 0.0f, GetMaxAccuracyPenalty());
		}
	}
}

void CWeaponSRS::ItemPreFrame()
{
	UpdatePenaltyTime();

	if (m_flChamberFinishTime <= gpGlobals->curtime && m_bRoundBeingChambered == true)
	{ // Finished chambering a round, enable Primary attack
		m_bRoundBeingChambered = false;
		m_bRoundChambered = true;
	}

	if (m_flNextPrimaryAttack <= gpGlobals->curtime && !m_bRoundChambered && !m_bRoundBeingChambered && m_iClip1 > 0)
	{ // Primary attack animation finished, begin chambering a round
		if (CNEO_Player* pOwner = static_cast<CNEO_Player*>(ToBasePlayer(GetOwner()))) {
			if (pOwner->m_nButtons & IN_ATTACK)
			{
				BaseClass::ItemPreFrame();
				return;
			}
			pOwner->Weapon_SetZoom(false);
		}
		m_bRoundBeingChambered = true;
		m_flChamberFinishTime = gpGlobals->curtime + GetFireRate();
		WeaponSound(SPECIAL1);
		SendWeaponAnim(ACT_VM_PULLBACK);
	}

	BaseClass::ItemPreFrame();
}

void CWeaponSRS::ItemBusyFrame()
{
	UpdatePenaltyTime();

	BaseClass::ItemBusyFrame();
}

void CWeaponSRS::ItemPostFrame()
{
	ProcessAnimationEvents();

	BaseClass::ItemPostFrame();
}

Activity CWeaponSRS::GetPrimaryAttackActivity()
{
	if (m_nNumShotsFired < 1)
	{
		return ACT_VM_PRIMARYATTACK;
	}

	if (m_nNumShotsFired < 2)
	{
		return ACT_VM_RECOIL1;
	}

	if (m_nNumShotsFired < 3)
	{
		return ACT_VM_RECOIL2;
	}

	return ACT_VM_RECOIL3;
}

void CWeaponSRS::AddViewKick()
{
	auto owner = ToBasePlayer(GetOwner());

	if (!owner)
	{
		return;
	}

	QAngle viewPunch;

	viewPunch.x = SharedRandomFloat("srspx", 0.25f, 0.5f);
	viewPunch.y = SharedRandomFloat("srspy", -0.6f, 0.6f);
	viewPunch.z = 0;

	owner->ViewPunch(viewPunch);
}
