//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_scenario_monitor.h
// Behavior layer that interrupts for scenario rules (picked up flag, drop what you're doing and capture, etc)
// Michael Booth, May 2011

#ifndef TF_BOT_SCENARIO_MONITOR_H
#define TF_BOT_SCENARIO_MONITOR_H

class CTFBotScenarioMonitor : public Action< HeatseakerBot >
{
public:
	virtual Action< HeatseakerBot > *InitialContainedAction( HeatseakerBot *me );

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual const char *GetName( void ) const	{ return "ScenarioMonitor"; }

private:
	CountdownTimer m_ignoreLostFlagTimer;
	CountdownTimer m_lostFlagTimer;

	virtual Action< HeatseakerBot > *DesiredScenarioAndClassAction( HeatseakerBot *me );
};


#endif // TF_BOT_SCENARIO_MONITOR_H
