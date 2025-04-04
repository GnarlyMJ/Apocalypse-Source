//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_locomotion.cpp
// Team Fortress NextBot locomotion interface
// Michael Booth, May 2010

#include "cbase.h"

#include "Heatseaker.h"
#include "Heatseaker_Locomotion.h"
#include "particle_parse.h"

//-----------------------------------------------------------------------------------------
void HeatseakerLocomotion::Update(void)
{
	BaseClass::Update();

	HeatseakerBot* me = toHeatseaker(GetBot()->GetEntity());
	if (!me)
	{
		return;
	}
}


//-----------------------------------------------------------------------------------------
// Move directly towards the given position
void HeatseakerLocomotion::Approach(const Vector& pos, float goalWeight)
{
	BaseClass::Approach(pos, goalWeight);
}


//-----------------------------------------------------------------------------------------
// Distance at which we will die if we fall
float HeatseakerLocomotion::GetDeathDropHeight(void) const
{
	return 1000.0f;
}


//-----------------------------------------------------------------------------------------
// Get maximum running speed
float HeatseakerLocomotion::GetRunSpeed(void) const
{
	return 100.0f;
}


//-----------------------------------------------------------------------------------------
// Return true if given area can be used for navigation
bool HeatseakerLocomotion::IsAreaTraversable(const CNavArea* baseArea) const
{
	HeatseakerBot* me = (HeatseakerBot*)GetBot()->GetEntity();

	if (baseArea->IsBlocked(me->GetTeamNumber()))
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------------
bool HeatseakerLocomotion::IsEntityTraversable(CBaseEntity* obstacle, TraverseWhenType when) const
{
	// assume all players are "traversable" in that they will move or can be killed
	if (obstacle && obstacle->IsPlayer())
	{
		return true;
	}

	return PlayerLocomotion::IsEntityTraversable(obstacle, when);
}


void HeatseakerLocomotion::Jump(void)
{
	BaseClass::Jump();

	HeatseakerBot* me = toHeatseaker(GetBot()->GetEntity());
	if (!me)
	{
		return;
	}
}