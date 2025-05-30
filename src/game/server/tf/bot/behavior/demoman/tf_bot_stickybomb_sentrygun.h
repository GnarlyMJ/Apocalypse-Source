//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_stickybomb_sentrygun.h
// Destroy the given sentrygun with stickybombs
// Michael Booth, August 2010

#ifndef TF_BOT_STICKYBOMB_SENTRY_H
#define TF_BOT_STICKYBOMB_SENTRY_H

class CObjectSentrygun;


class CTFBotStickybombSentrygun : public Action< HeatseakerBot >
{
public:
	CTFBotStickybombSentrygun( CObjectSentrygun *sentrygun );
	CTFBotStickybombSentrygun( CObjectSentrygun *sentrygun, float aimYaw, float aimPitch, float aimCharge );

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );
	virtual void					OnEnd( HeatseakerBot *me, Action< HeatseakerBot > *nextAction );

	virtual ActionResult< HeatseakerBot >	OnSuspend( HeatseakerBot *me, Action< HeatseakerBot > *interruptingAction );

	virtual EventDesiredResult< HeatseakerBot > OnInjured( HeatseakerBot *me, const CTakeDamageInfo &info );

	virtual QueryResultType ShouldHurry( const INextBot *me ) const;
	virtual QueryResultType	ShouldAttack( const INextBot *me, const CKnownEntity *them ) const;	// should we attack "them"?
	virtual QueryResultType ShouldRetreat( const INextBot *me ) const;					// is it time to retreat?

	virtual const char *GetName( void ) const	{ return "StickybombSentrygun"; };

private:
	float m_givenYaw, m_givenPitch, m_givenCharge;
	bool m_hasGivenAim;

	bool m_isFullReloadNeeded;

	CHandle< CObjectSentrygun > m_sentrygun;

	bool m_isChargingShot;

	CountdownTimer m_searchTimer;
	bool m_hasTarget;
	Vector m_eyeAimTarget;
	Vector m_launchSpot;
	float m_chargeToLaunch;
	float m_searchPitch;
	bool IsAimOnTarget( HeatseakerBot *me, float pitch, float yaw, float charge );
};

#endif // TF_BOT_STICKYBOMB_SENTRY_H
