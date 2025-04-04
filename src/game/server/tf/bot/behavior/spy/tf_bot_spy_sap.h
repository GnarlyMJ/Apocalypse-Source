//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_spy_sap.h
// Sap nearby enemy buildings
// Michael Booth, June 2010

#ifndef TF_BOT_SPY_SAP_H
#define TF_BOT_SPY_SAP_H

#include "Path/NextBotPathFollow.h"

class CTFBotSpySap : public Action< HeatseakerBot >
{
public:
	CTFBotSpySap( CBaseObject *sapTarget );
	virtual ~CTFBotSpySap() { }

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );
	virtual void					OnEnd( HeatseakerBot *me, Action< HeatseakerBot > *nextAction );

	virtual ActionResult< HeatseakerBot >	OnSuspend( HeatseakerBot *me, Action< HeatseakerBot > *interruptingAction );
	virtual ActionResult< HeatseakerBot >	OnResume( HeatseakerBot *me, Action< HeatseakerBot > *interruptingAction );

	virtual EventDesiredResult< HeatseakerBot > OnStuck( HeatseakerBot *me );

	virtual QueryResultType ShouldAttack( const INextBot *me, const CKnownEntity *them ) const;	// should we attack "them"?
	virtual QueryResultType	ShouldRetreat( const INextBot *me ) const;							// is it time to retreat?
	virtual QueryResultType IsHindrance( const INextBot *me, CBaseEntity *blocker ) const;		// use this to signal the enemy we are focusing on, so we dont avoid them

	virtual const char *GetName( void ) const	{ return "SpySap"; };

private:
	CHandle< CBaseObject > m_sapTarget;

	CountdownTimer m_repathTimer;
	PathFollower m_path;

	CBaseObject *GetNearestKnownSappableTarget( HeatseakerBot *me );
	bool AreAllDangerousSentriesSapped( HeatseakerBot *me ) const;
};

#endif // TF_BOT_SPY_SAP_H
