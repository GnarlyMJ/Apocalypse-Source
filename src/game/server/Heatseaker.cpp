/*
* Heatseaker.cpp
* This is the main file for the Heatseaker Nextbot
*/

#include "cbase.h"
#include "Heatseaker.h"

#include "NextBot.h"
#include "NextBotVisionInterface.h"
#include "NextBotBodyInterface.h"
#include "NextBotUtil.h"

/*
* Command to spawn heatseaker
*/

CON_COMMAND_F(Heatseaker_add, "Spawn A Heatseaker At Crosshair", FCVAR_CHEAT)
{
	CBasePlayer* player = UTIL_GetCommandClient();
	if (!player)
	{
		return;
	}

	Vector forward;
	player->EyeVectors(&forward);

	trace_t result;
	UTIL_TraceLine(player->EyePosition(), player->EyePosition() + 999999.9f * forward, MASK_BLOCKLOS_AND_NPCS | CONTENTS_IGNORE_NODRAW_OPAQUE, player, COLLISION_GROUP_NONE, &result);
	if (!result.DidHit())
	{
		return;
	}

	HeatseakerBot* bot = static_cast<HeatseakerBot*>(CreateEntityByName("Heatseaker"));
	if (bot)
	{
		Vector forward = player->GetAbsOrigin() - result.endpos;
		forward.z = 0.0f;
		forward.NormalizeInPlace();

		QAngle angles;
		VectorAngles(forward, angles);

		bot->SetAbsAngles(angles);
		bot->SetAbsOrigin(result.endpos + Vector(0, 0, 10.0f));

		DispatchSpawn(bot);
	}
}

//-----------------------------------------------------------------------------------------------------
// The Simple Bot
//-----------------------------------------------------------------------------------------------------
LINK_ENTITY_TO_CLASS(Heatseaker, HeatseakerBot);


//-----------------------------------------------------------------------------------------------------
HeatseakerBot::HeatseakerBot()
{
	ALLOCATE_INTENTION_INTERFACE(HeatseakerBot);

	m_locomotor = new NextBotGroundLocomotion(this);
}


//-----------------------------------------------------------------------------------------------------
HeatseakerBot::~HeatseakerBot()
{
	DEALLOCATE_INTENTION_INTERFACE;

	if (m_locomotor)
		delete m_locomotor;
}

//-----------------------------------------------------------------------------------------------------
void HeatseakerBot::Precache()
{
	BaseClass::Precache();

#ifndef DOTA_DLL
	PrecacheModel("models/vortigaunt.mdl");
#endif
}


//-----------------------------------------------------------------------------------------------------
void HeatseakerBot::Spawn(void)
{
	BaseClass::Spawn();

#ifndef DOTA_DLL
	SetModel("models/vortigaunt.mdl");
#endif
}


//---------------------------------------------------------------------------------------------
// The Simple Bot behaviors
//---------------------------------------------------------------------------------------------
/**
 * For use with TheNavMesh->ForAllAreas()
 * Find the Nth area in the sequence
 */
class SelectNthAreaFunctor
{
public:
	SelectNthAreaFunctor(int count)
	{
		m_count = count;
		m_area = NULL;
	}

	bool operator() (CNavArea* area)
	{
		m_area = area;
		return (m_count-- > 0);
	}

	int m_count;
	CNavArea* m_area;
};


//---------------------------------------------------------------------------------------------
/**
 * This action causes the bot to pick a random nav area in the mesh and move to it, then
 * pick another, etc.
 * Actions usually each have their own .cpp/.h file and are organized into folders since there
 * are often many of them. For this example, we're keeping everything to a single .cpp/.h file.
 */
class CSimpleBotRoam : public Action< HeatseakerBot >
{
public:
	//----------------------------------------------------------------------------------
	// OnStart is called once when the Action first becomes active
	virtual ActionResult< HeatseakerBot >	OnStart(HeatseakerBot* me, Action< HeatseakerBot >* priorAction)
	{
		// smooth out the bot's path following by moving toward a point farther down the path
		m_path.SetMinLookAheadDistance(300.0f);

		return Continue();
	}


	//----------------------------------------------------------------------------------
	// Update is called repeatedly (usually once per server frame) while the Action is active
	virtual ActionResult< HeatseakerBot >	Update(HeatseakerBot* me, float interval)
	{
		if (m_path.IsValid() && !m_timer.IsElapsed())
		{
			// PathFollower::Update() moves the bot along the path using the bot's ILocomotion and IBody interfaces
			m_path.Update(me);
		}
		else
		{
			SelectNthAreaFunctor pick(RandomInt(0, TheNavMesh->GetNavAreaCount() - 1));
			TheNavMesh->ForAllAreas(pick);

			if (pick.m_area)
			{
				CSimpleBotPathCost cost(me);
				m_path.Compute(me, pick.m_area->GetCenter(), cost);
			}

			// follow this path for a random duration (or until we reach the end)
			m_timer.Start(RandomFloat(5.0f, 10.0f));
		}

		return Continue();
	}


	//----------------------------------------------------------------------------------
	// this is an event handler - many more are available (see declaration of Action< Actor > in NextBotBehavior.h)
	virtual EventDesiredResult< HeatseakerBot > OnStuck(HeatseakerBot* me)
	{
		// we are stuck trying to follow the current path - invalidate it so a new one is chosen
		m_path.Invalidate();

		return TryContinue();
	}


	virtual const char* GetName(void) const { return "Roam"; }		// return name of this action

private:
	PathFollower m_path;
	CountdownTimer m_timer;
};


//---------------------------------------------------------------------------------------------
/**
 * Instantiate the bot's Intention interface and start the initial Action (CSimpleBotRoam in this case)
 */
IMPLEMENT_INTENTION_INTERFACE(HeatseakerBot, CSimpleBotRoam)