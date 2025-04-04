//========= Copyright Valve Corporation, All rights reserved. ============//
// Michael Booth, September 2012

#ifndef TF_BOT_MVM_ENGINEER_BUILD_SENTRYGUN_H
#define TF_BOT_MVM_ENGINEER_BUILD_SENTRYGUN_H

class CTFBotHintSentrygun;

class CTFBotMvMEngineerBuildSentryGun : public Action< HeatseakerBot >
{
public:
	CTFBotMvMEngineerBuildSentryGun( CTFBotHintSentrygun* pSentryHint );

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );
	virtual void					OnEnd( HeatseakerBot *me, Action< HeatseakerBot > *nextAction );

	virtual const char *GetName( void ) const	{ return "MvMEngineerBuildSentryGun"; };

private:
	CHandle< CTFBotHintSentrygun > m_sentryBuildHint;
	CHandle< CObjectSentrygun > m_sentry;

	CountdownTimer m_delayBuildTime;
	CountdownTimer m_repathTimer;
	PathFollower m_path;
};

#endif // TF_BOT_MVM_ENGINEER_BUILD_SENTRYGUN_H
