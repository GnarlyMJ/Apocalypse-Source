//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_wander.h
// Wanderering/idle enemies for Squad Co-op mode
// Michael Booth, October 2009

#ifndef TF_BOT_WANDER_H
#define TF_BOT_WANDER_H

#ifdef TF_RAID_MODE

//-----------------------------------------------------------------------------
class CTFBotWander : public Action< HeatseakerBot >
{
public:
	CTFBotWander( void );

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual EventDesiredResult< HeatseakerBot > OnContact( HeatseakerBot *me, CBaseEntity *other, CGameTrace *result = NULL );
	virtual EventDesiredResult< HeatseakerBot > OnInjured( HeatseakerBot *me, const CTakeDamageInfo &info );
	virtual EventDesiredResult< HeatseakerBot > OnOtherKilled( HeatseakerBot *me, CBaseCombatCharacter *victim, const CTakeDamageInfo &info );

	virtual EventDesiredResult< HeatseakerBot > OnCommandAttack( HeatseakerBot *me, CBaseEntity *victim );

	virtual QueryResultType ShouldHurry( const INextBot *me ) const;					// are we in a hurry?
	virtual QueryResultType	ShouldRetreat( const INextBot *me ) const;							// is it time to retreat?

	virtual const char *GetName( void ) const	{ return "Wander"; };

private:
	CountdownTimer m_visionTimer;
	CountdownTimer m_vocalizeTimer;
};


inline QueryResultType CTFBotWander::ShouldHurry( const INextBot *me ) const
{
	return ANSWER_YES;
}


inline QueryResultType CTFBotWander::ShouldRetreat( const INextBot *me ) const
{
	return ANSWER_NO;
}


#endif TF_RAID_MODE

#endif // TF_BOT_WANDER_H
