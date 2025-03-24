//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
// This is a skeleton file for use when creating a new 
// NPC. Copy and rename this file for the new
// NPC and add the copy to the build.
//
// Replace occurrences of CNPC_New with the new NPC's
// classname. Don't forget the lower-case occurrence in 
// LINK_ENTITY_TO_CLASS()
//
//
// ASSUMPTIONS MADE:
//
// You're making a character based on CAI_BaseNPC. If this 
// is not true, make sure you replace all occurrences
// of 'CAI_BaseNPC' in this file with the appropriate 
// parent class.
//
// You're making a human-sized NPC that walks.
//
//=============================================================================//
#include "cbase.h"
#include "ai_default.h"
#include "ai_task.h"
#include "ai_schedule.h"
#include "ai_hull.h"
#include "ai_squad.h"
#include "soundent.h"
#include "game.h"
#include "npcevent.h"
#include "entitylist.h"
#include "activitylist.h"
#include "ai_basenpc.h"
#include "engine/IEngineSound.h"

#define NPC_NEW_MODEL "models/mymodel.mdl"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//=========================================================
// Private animevents
//=========================================================
int NEWNPC_AE_ANIMEVENT;
int NEWNPC_AE_ANIMEVENT2;

//=========================================================
// Private activities
//=========================================================
Activity ACT_NEWNPC_ACTIVITY;
Activity ACT_NEWNPC_ACTIVITY2;

//=========================================================
// Shared interaction
//=========================================================
int g_interactionExample = 0; // REMEMBER TO ADD THIS TO AI_Interactions.h
int g_interactionExample2 = 0; // REMEMBER TO ADD THIS TO AI_Interactions.h

// -----------------------------------------------
//	> Squad slots
// -----------------------------------------------
enum SquadSlot_T
{
	SQUAD_SLOT_EXAMPLE = LAST_SHARED_SQUADSLOT,
	SQUAD_SLOT_EXAMPLE2,
};

//=========================================================
//=========================================================
class CNPC_New : public CAI_BaseNPC
{
	DECLARE_CLASS(CNPC_New, CAI_BaseNPC);
	DECLARE_DATADESC();
	DEFINE_CUSTOM_AI;

public:
	void	Precache(void);
	void	Spawn(void);
	Class_T Classify(void);
private:
	enum
	{
		SCHED_NEWNPC_SCHEDULE = BaseClass::NEXT_SCHEDULE,
		SCHED_NEWNPC_SCHEDULE2,
		NEXT_SCHEDULE
	};

	enum
	{
		TASK_NEWNPC_TASK = BaseClass::NEXT_TASK,
		TASK_NEWNPC_TASK2,
		NEXT_TASK
	};

	enum
	{
		COND_NEWNPC_CONDITION = BaseClass::NEXT_CONDITION,
		COND_NEWNPC_CONDITION2,
		NEXT_CONDITION
	};
};

LINK_ENTITY_TO_CLASS(npc_newnpc, CNPC_New);

//---------------------------------------------------------
// Save/Restore
//---------------------------------------------------------
BEGIN_DATADESC(CNPC_New)

END_DATADESC()

AI_BEGIN_CUSTOM_NPC(npc_newnpc, CNPC_New)

AI_END_CUSTOM_NPC()

//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
void CNPC_New::Precache(void)
{
	PrecacheModel(NPC_NEW_MODEL);

	BaseClass::Precache();
}

//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
void CNPC_New::Spawn(void)
{
	Precache();

	SetModel(NPC_NEW_MODEL);
	SetHullType(HULL_HUMAN);
	SetHullSizeNormal();

	SetSolid(SOLID_BBOX);
	AddSolidFlags(FSOLID_NOT_STANDABLE);
	SetMoveType(MOVETYPE_STEP);
	SetBloodColor(BLOOD_COLOR_RED);
	m_iHealth = 20;
	m_flFieldOfView = 0.5; // indicates the width of this NPC's forward view cone ( as a dotproduct result )
	m_NPCState = NPC_STATE_NONE;

	CapabilitiesClear();
	CapabilitiesAdd(bits_CAP_TURN_HEAD | bits_CAP_MOVE_GROUND);

	NPCInit();
}

//-----------------------------------------------------------------------------
// Purpose: 
//
//
// Output : 
//-----------------------------------------------------------------------------
Class_T	CNPC_New::Classify(void)
{
	return	CLASS_NONE;
}