//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_squad_attack.h
// Move and attack as a small, cohesive, group
// Michael Booth, October 2009

#ifndef TF_BOT_SQUAD_ATTACK_H
#define TF_BOT_SQUAD_ATTACK_H

#ifdef TF_RAID_MODE

#include "Path/NextBotPathFollow.h"
#include "Path/NextBotChasePath.h"


//-----------------------------------------------------------------------------
class CTFBotSquadAttack : public Action< HeatseakerBot >
{
public:
	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual ActionResult< HeatseakerBot >	OnResume( HeatseakerBot *me, Action< HeatseakerBot > *interruptingAction );

	virtual EventDesiredResult< HeatseakerBot > OnStuck( HeatseakerBot *me );

	QueryResultType	ShouldRetreat( const INextBot *me ) const;

	virtual const char *GetName( void ) const	{ return "SquadPatrol"; };

private:
	CountdownTimer m_vocalizeTimer;
	PathFollower m_path;
	ChasePath m_chasePath;
	CHandle< CTFPlayer > m_victim;
	CountdownTimer m_victimConsiderTimer;

	HeatseakerBot *GetSquadLeader( HeatseakerBot *me ) const;
};

inline QueryResultType CTFBotSquadAttack::ShouldRetreat( const INextBot *me ) const
{
	return ANSWER_NO;
}

#endif // TF_RAID_MODE

#endif // TF_BOT_SQUAD_ATTACK_H
