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
#include <ai_behavior_assault.h>
#include "util.h"
#include "networkvar.h"

#define NPC_NEW_MODEL "models/alyx.mdl"

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
class CNPC_Heatseaker : public CAI_BaseNPC
{
	DECLARE_CLASS(CNPC_Heatseaker, CAI_BaseNPC);
	DECLARE_DATADESC();
	DEFINE_CUSTOM_AI;

public:
	void	Precache(void);
	void	Spawn(void);
	void GatherConditions();
	int SelectSchedule(void);
	void StartTask(const Task_t* pTask);
	//bool ChooseEnemy();
	//void SetEnemy(CBaseEntity* pEnemy, bool bSetCondNewEnemy);
	//CBaseEntity* GetEnemy();
	//CBaseCombatCharacter* GetEnemyCombatCharacterPointer();
	//float GetTimeEnemyAcquired();
	//void OnEnemyChanged(CBaseEntity* pOldEnemy, CBaseEntity* pNewEnemy);
	//bool UpdateEnemyMemory(CBaseEntity* pEnemy, const Vector& position, CBaseEntity* pInformer);
	//Vector GetEnemyLKP();
	//float GetEnemyLastTimeSeen();
	//void MarkEnemyAsEluded();
	//bool EnemyHasEludedMe();
	Class_T Classify(void);
private:
	enum
	{
		SCHED_HEATSEAKER_HUNTING = BaseClass::NEXT_SCHEDULE,
		SCHED_HEATSEAKER_RESTING = BaseClass::NEXT_SCHEDULE,
		SCHED_HEATSEAKER_TRACKING = BaseClass::NEXT_SCHEDULE,
		NEXT_SCHEDULE
	};

	enum
	{
		TASK_HEATSEAKER_FOLLOW = BaseClass::NEXT_TASK,
		TASK_HEATSEAKER_REST = BaseClass::NEXT_TASK,
		NEXT_TASK
	};

	enum
	{
		COND_HEATSEAKER_SEEN_PREY = BaseClass::NEXT_CONDITION,
		COND_HEATSEAKER_LOST_PREY = BaseClass::NEXT_CONDITION,
		NEXT_CONDITION
	};
};

LINK_ENTITY_TO_CLASS(cnpc_heatseaker, CNPC_Heatseaker);

//---------------------------------------------------------
// Save/Restore
//---------------------------------------------------------
BEGIN_DATADESC(CNPC_Heatseaker)

END_DATADESC()

AI_BEGIN_CUSTOM_NPC(cnpc_heatseaker, CNPC_Heatseaker)
	DECLARE_CONDITION(COND_HEATSEAKER_SEEN_PREY);
	DECLARE_CONDITION(COND_HEATSEAKER_LOST_PREY);
	DECLARE_TASK(TASK_HEATSEAKER_FOLLOW);
	DECLARE_TASK(TASK_HEATSEAKER_REST);
	DEFINE_SCHEDULE
	(
		SCHED_HEATSEAKER_HUNTING,
		"	Tasks"
		"		TASK_WANDER	25 100000"
		""
		"	Interrups"
		"		COND_HEATSEAKER_SEEN_PREY"
	)
	DEFINE_SCHEDULE
	(
		SCHED_HEATSEAKER_RESTING,
		"	Tasks"
		"		TASK_HEATSEAKER_REST	0"
		""
		"	Interrups"
		"		COND_HEATSEAKER_SEEN_PREY"
	)
	DEFINE_SCHEDULE
	(
		SCHED_HEATSEAKER_TRACKING,
		"	Tasks"
		"		TASK_HEATSEAKER_FOLLOW	0"
		""
		"	Interrups"
		"		COND_HEATSEAKER_LOST_PREY"
	)
AI_END_CUSTOM_NPC()

//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
void CNPC_Heatseaker::Precache(void)
{
	PrecacheModel(NPC_NEW_MODEL);

	BaseClass::Precache();
}

//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
void CNPC_Heatseaker::Spawn(void)
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


//Gather conditions method, Also handles logic
void CNPC_Heatseaker::GatherConditions()
{ 
	BaseClass::GatherConditions();
	SetCondition(COND_HEATSEAKER_SEEN_PREY);
}
/* BROKEN
void CAI_AssaultBehavior::BuildScheduleTestBits()
{
	BaseClass::BuildScheduleTestBits();

	//If we are allowed to divert, add the appropriate interups to our movement schedules
	if (m_hAssaultPoint && m_hAssaultPoint->m_bAllowDiversion)
	{
		if (IsCurSchedule(SCHED_MOVE_TO_ASSAULT_POINT) || IsCurSchedule(SCHED_MOVE_TO_RALLY_POINT) || IsCurSchedule(SCHED_HOLD_RALLY_POINT))
		{
			GetOuter()->SetCustomInterruptCondition(COND_NEW_ENEMY);
			GetOuter()->SetCustomInterruptCondition(COND_SEE_ENEMY);
		}
	}
}
*/
int CNPC_Heatseaker::SelectSchedule(void)
{
	if (HasCondition(COND_HEATSEAKER_SEEN_PREY))
	{
		return SCHED_HEATSEAKER_TRACKING;
	}
	else if (HasCondition(COND_HEATSEAKER_LOST_PREY))
	{
		return SCHED_HEATSEAKER_HUNTING;
	}
	else
	{
		return BaseClass::SelectSchedule();
	}
}

void CNPC_Heatseaker::StartTask(const Task_t* pTask)
{
	switch (pTask->iTask)
	{
		default:
			BaseClass::StartTask(pTask);
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//
//
// Output : 
//-----------------------------------------------------------------------------
Class_T	CNPC_Heatseaker::Classify(void)
{
	return	CLASS_NONE;
}
