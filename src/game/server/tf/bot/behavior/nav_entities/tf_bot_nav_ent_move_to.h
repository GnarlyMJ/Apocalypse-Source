//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_nav_ent_move_to.h
// Move onto target and wait, as directed by nav entity
// Michael Booth, September 2009

#ifndef TF_BOT_NAV_ENT_MOVE_TO_H
#define TF_BOT_NAV_ENT_MOVE_TO_H

#include "Path/NextBotPathFollow.h"
#include "NextBot/NavMeshEntities/func_nav_prerequisite.h"


class CTFBotNavEntMoveTo : public Action< HeatseakerBot >
{
public:
	CTFBotNavEntMoveTo( const CFuncNavPrerequisite *prereq );

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual const char *GetName( void ) const	{ return "NavEntMoveTo"; };

private:
	CHandle< CFuncNavPrerequisite > m_prereq;
	Vector m_goalPosition;				// specific position within entity to move to
	CTFNavArea* m_pGoalArea;

	CountdownTimer m_waitTimer;

	PathFollower m_path;				// how we get to the loot
	CountdownTimer m_repathTimer;
};


#endif // TF_BOT_NAV_ENT_MOVE_TO_H
