//========= Copyright Valve Corporation, All rights reserved. ============//
// Michael Booth, September 2012

#ifndef TF_BOT_MVM_ENGINEER_IDLE_H
#define TF_BOT_MVM_ENGINEER_IDLE_H

#include "Path/NextBotPathFollow.h"

class CBaseTFBotHintEntity;
class CTFBotHintSentrygun;
class CTFBotHintTeleporterExit;
class CTFBotHintEngineerNest;

class CTFBotMvMEngineerIdle : public Action< HeatseakerBot >
{
public:
	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual QueryResultType ShouldAttack( const INextBot *me, const CKnownEntity *them ) const;
	virtual QueryResultType	ShouldRetreat( const INextBot *me ) const;							// is it time to retreat?
	virtual QueryResultType	ShouldHurry( const INextBot *me ) const;							// are we in a hurry?

	virtual const char *GetName( void ) const	{ return "MvMEngineerIdle"; };

private:
	PathFollower m_path;
	CountdownTimer m_repathTimer;
	CountdownTimer m_sentryInjuredTimer;
	CountdownTimer m_sentryRebuildTimer;
	CountdownTimer m_teleporterRebuildTimer;
	CountdownTimer m_findHintTimer;
	CountdownTimer m_reevaluateNestTimer;

	int m_nTeleportedCount;
	bool m_bTeleportedToHint;
	CHandle< CTFBotHintTeleporterExit > m_teleporterHint;
	CHandle< CTFBotHintSentrygun > m_sentryHint;
	CHandle< CTFBotHintEngineerNest > m_nestHint;

	void TakeOverStaleNest( CBaseTFBotHintEntity* pHint, HeatseakerBot *me );
	bool ShouldAdvanceNestSpot( HeatseakerBot *me );

	void TryToDetonateStaleNest();
	bool m_bTriedToDetonateStaleNest;
};

class CTFBotMvMEngineerHintFinder
{
public:
	static bool FindHint( bool bShouldCheckForBlockingObjects, bool bAllowOutOfRangeNest, CHandle< CTFBotHintEngineerNest >* pFoundNest = NULL );
};


#endif // TF_BOT_MVM_ENGINEER_IDLE_H
