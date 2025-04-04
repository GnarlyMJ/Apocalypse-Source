//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_sniper_lurk.h
// Move into position and wait for victims
// Michael Booth, October 2009

#ifndef TF_BOT_SNIPER_LURK_H
#define TF_BOT_SNIPER_LURK_H

#include "Path/NextBotPathFollow.h"

class CTFBotHint;

class CTFBotSniperLurk : public Action< HeatseakerBot >
{
public:
	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );
	virtual void					OnEnd( HeatseakerBot *me, Action< HeatseakerBot > *nextAction );
	virtual ActionResult< HeatseakerBot >	OnSuspend( HeatseakerBot *me, Action< HeatseakerBot > *interruptingAction );
	virtual ActionResult< HeatseakerBot >	OnResume( HeatseakerBot *me, Action< HeatseakerBot > *interruptingAction );

	// Snipers choose their targets a bit differently
	virtual const CKnownEntity *	SelectMoreDangerousThreat( const INextBot *me, 
															   const CBaseCombatCharacter *subject,
															   const CKnownEntity *threat1, 
															   const CKnownEntity *threat2 ) const;	// return the more dangerous of the two threats to 'subject', or NULL if we have no opinion

	virtual QueryResultType ShouldAttack( const INextBot *me, const CKnownEntity *them ) const;	// should we attack "them"?
	virtual QueryResultType ShouldRetreat( const INextBot *me ) const;							// is it time to retreat?

	virtual const char *GetName( void ) const	{ return "SniperLurk"; };

private:
	CountdownTimer m_boredTimer;
	CountdownTimer m_repathTimer;
	PathFollower m_path;
	int m_failCount;

	Vector m_homePosition;			// where we want to snipe from
	bool m_isHomePositionValid;
	bool m_isAtHome;
	bool FindNewHome( HeatseakerBot *me );
	CountdownTimer m_findHomeTimer;
	bool m_isOpportunistic;

	CUtlVector< CHandle< CTFBotHint > > m_hintVector;
	CHandle< CTFBotHint > m_priorHint;
	bool FindHint( HeatseakerBot *me );
};

#endif // TF_BOT_SNIPER_LURK_H
