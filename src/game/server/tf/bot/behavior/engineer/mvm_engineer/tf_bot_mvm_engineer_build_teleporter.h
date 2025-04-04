//========= Copyright Valve Corporation, All rights reserved. ============//
// Michael Booth, September 2012

#ifndef TF_BOT_MVM_ENGINEER_BUILD_TELEPORTER_H
#define TF_BOT_MVM_ENGINEER_BUILD_TELEPORTER_H

class CTFBotHintTeleporterExit;

class CTFBotMvMEngineerBuildTeleportExit : public Action< HeatseakerBot >
{
public:
	CTFBotMvMEngineerBuildTeleportExit( CTFBotHintTeleporterExit *hint );

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual const char *GetName( void ) const	{ return "MvMEngineerBuildTeleportExit"; };

private:
	CHandle< CTFBotHintTeleporterExit > m_teleporterBuildHint;

	CountdownTimer m_delayBuildTime;
	CountdownTimer m_repathTimer;
	PathFollower m_path;
};

#endif // TF_BOT_MVM_ENGINEER_BUILD_TELEPORTER_H
