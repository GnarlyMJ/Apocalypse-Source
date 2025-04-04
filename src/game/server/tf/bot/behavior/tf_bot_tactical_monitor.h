//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_tactical_monitor.h
// Behavior layer that interrupts for ammo/health/retreat/etc
// Michael Booth, June 2009

#ifndef TF_BOT_TACTICAL_MONITOR_H
#define TF_BOT_TACTICAL_MONITOR_H

class CObjectTeleporter;

class CTFBotTacticalMonitor : public Action< HeatseakerBot >
{
public:
	virtual Action< HeatseakerBot > *InitialContainedAction( HeatseakerBot *me );

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual EventDesiredResult< HeatseakerBot > OnNavAreaChanged( HeatseakerBot *me, CNavArea *newArea, CNavArea *oldArea );
	virtual EventDesiredResult< HeatseakerBot > OnOtherKilled( HeatseakerBot *me, CBaseCombatCharacter *victim, const CTakeDamageInfo &info );

	// @note Tom Bui: Currently used for the training stuff, but once we get that interface down, we will turn that
	// into a proper API
	virtual EventDesiredResult< HeatseakerBot > OnCommandString( HeatseakerBot *me, const char *command );

	virtual const char *GetName( void ) const	{ return "TacticalMonitor"; }

private:
	CountdownTimer m_maintainTimer;

	CountdownTimer m_acknowledgeAttentionTimer;
	CountdownTimer m_acknowledgeRetryTimer;
	CountdownTimer m_attentionTimer;

	CountdownTimer m_stickyBombCheckTimer;
	void MonitorArmedStickyBombs( HeatseakerBot *me );

	bool ShouldOpportunisticallyTeleport( HeatseakerBot *me ) const;
	CObjectTeleporter *FindNearbyTeleporter( HeatseakerBot *me );
	CountdownTimer m_findTeleporterTimer;

	void AvoidBumpingEnemies( HeatseakerBot *me );
};



#endif // TF_BOT_TACTICAL_MONITOR_H
