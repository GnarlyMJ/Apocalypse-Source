//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_mob_rush.h
// A member of a rushing mob of melee attackers
// Michael Booth, October 2009

#ifndef TF_BOT_MOB_RUSH_H
#define TF_BOT_MOB_RUSH_H

#ifdef TF_RAID_MODE

#include "Path/NextBotChasePath.h"


//-----------------------------------------------------------------------------
class CTFBotMobRush : public Action< HeatseakerBot >
{
public:
	CTFBotMobRush( CTFPlayer *victim, float reactionTime = 0.0f );

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual EventDesiredResult< HeatseakerBot > OnContact( HeatseakerBot *me, CBaseEntity *other, CGameTrace *result = NULL );
	virtual EventDesiredResult< HeatseakerBot > OnInjured( HeatseakerBot *me, const CTakeDamageInfo &info );
	virtual EventDesiredResult< HeatseakerBot > OnOtherKilled( HeatseakerBot *me, CBaseCombatCharacter *victim, const CTakeDamageInfo &info );
	virtual EventDesiredResult< HeatseakerBot > OnStuck( HeatseakerBot *me );

	QueryResultType	ShouldRetreat( const INextBot *me ) const;

	virtual const char *GetName( void ) const	{ return "MobRush"; };

private:
	CHandle< CTFPlayer > m_victim;
	CountdownTimer m_reactionTimer;
	CountdownTimer m_tauntTimer;
	CountdownTimer m_vocalizeTimer;
	ChasePath m_path;
};

#endif // TF_RAID_MODE

#endif // TF_BOT_MOB_RUSH_H
