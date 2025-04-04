//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_spy_infiltrate.h
// Move into position behind enemy lines and wait for victims
// Michael Booth, June 2010

#ifndef TF_BOT_SPY_INFILTRATE_H
#define TF_BOT_SPY_INFILTRATE_H

#include "Path/NextBotPathFollow.h"

class CTFBotSpyInfiltrate : public Action< HeatseakerBot >
{
public:
	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );
	virtual void					OnEnd( HeatseakerBot *me, Action< HeatseakerBot > *nextAction );
	virtual ActionResult< HeatseakerBot >	OnSuspend( HeatseakerBot *me, Action< HeatseakerBot > *interruptingAction );
	virtual ActionResult< HeatseakerBot >	OnResume( HeatseakerBot *me, Action< HeatseakerBot > *interruptingAction );

	virtual EventDesiredResult< HeatseakerBot > OnStuck( HeatseakerBot *me );
	virtual EventDesiredResult< HeatseakerBot > OnTerritoryCaptured( HeatseakerBot *me, int territoryID );
	virtual EventDesiredResult< HeatseakerBot > OnTerritoryLost( HeatseakerBot *me, int territoryID );

	virtual QueryResultType ShouldAttack( const INextBot *me, const CKnownEntity *them ) const;	// should we attack "them"?

	virtual const char *GetName( void ) const	{ return "SpyInfiltrate"; };

private:
	CountdownTimer m_repathTimer;
	PathFollower m_path;

	CTFNavArea *m_hideArea;
	bool FindHidingSpot( HeatseakerBot *me );
	CountdownTimer m_findHidingSpotTimer;

	CountdownTimer m_waitTimer;

	bool m_hasEnteredCombatZone;
};


#endif // TF_BOT_SPY_INFILTRATE_H
