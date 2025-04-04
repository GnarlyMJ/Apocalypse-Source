//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_nav_ent_wait.h
// Wait for awhile, as directed by nav entity
// Michael Booth, September 2009

#ifndef TF_BOT_NAV_ENT_WAIT_H
#define TF_BOT_NAV_ENT_WAIT_H

#include "NextBot/NavMeshEntities/func_nav_prerequisite.h"


class CTFBotNavEntWait : public Action< HeatseakerBot >
{
public:
	CTFBotNavEntWait( const CFuncNavPrerequisite *prereq );

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual const char *GetName( void ) const	{ return "NavEntWait"; };

private:
	CHandle< CFuncNavPrerequisite > m_prereq;
	CountdownTimer m_timer;
};


#endif // TF_BOT_NAV_ENT_WAIT_H
