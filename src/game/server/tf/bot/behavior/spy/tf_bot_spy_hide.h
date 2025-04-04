//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_spy_hide.h
// Move to a hiding spot
// Michael Booth, September 2011

#ifndef TF_BOT_SPY_HIDE
#define TF_BOT_SPY_HIDE

#include "Path/NextBotPathFollow.h"

class CTFBotSpyHide : public Action< HeatseakerBot >
{
public:
	CTFBotSpyHide( CTFPlayer *victim = NULL );
	virtual ~CTFBotSpyHide() { }

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual ActionResult< HeatseakerBot >	OnResume( HeatseakerBot *me, Action< HeatseakerBot > *interruptingAction );

	virtual EventDesiredResult< HeatseakerBot > OnMoveToSuccess( HeatseakerBot *me, const Path *path );
	virtual EventDesiredResult< HeatseakerBot > OnMoveToFailure( HeatseakerBot *me, const Path *path, MoveToFailureType reason );

	virtual QueryResultType ShouldAttack( const INextBot *me, const CKnownEntity *them ) const;	// should we attack "them"?

	virtual const char *GetName( void ) const	{ return "SpyHide"; };

private:
	CHandle< CTFPlayer > m_initialVictim;

	HidingSpot *m_hidingSpot;
	bool FindHidingSpot( HeatseakerBot *me );
	CountdownTimer m_findTimer;

	PathFollower m_path;
	CountdownTimer m_repathTimer;
	bool m_isAtGoal;

	float m_incursionThreshold;

	CountdownTimer m_talkTimer;
};

#endif // TF_BOT_SPY_HIDE
