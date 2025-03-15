#include "cbase.h"
#include "npcevent.h"
#include "in_buttons.h"

#ifdef CLIENT_DLL
	#include "c_hl2mp_player.h"
#else
	#include "hl2mp_player.h"
#endif

#include "weapon_hl2mpbasehlmpcombatweapon.h"

#define ROF 0.075f //RPS, 60sec/800 rounds = 0.075

#define BURST 500;

#ifdef CLIENT_DLL
	#define CWeaponAK47 C_WeaponAK47
#endif

class CWeaponAK47 : public CBaseHL2MPCombatWeapon
{ };