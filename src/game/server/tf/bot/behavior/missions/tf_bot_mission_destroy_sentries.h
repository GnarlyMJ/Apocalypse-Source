//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_mission_destroy_sentries.h
// Seek and destroy enemy sentries and ignore everything else
// Michael Booth, June 2011

#ifndef TF_BOT_MISSION_DESTROY_SENTRIES_H
#define TF_BOT_MISSION_DESTROY_SENTRIES_H


//-----------------------------------------------------------------------------
class CTFBotMissionDestroySentries : public Action< HeatseakerBot >
{
public:
	CTFBotMissionDestroySentries( CObjectSentrygun *goalSentry = NULL );
	virtual ~CTFBotMissionDestroySentries() { }

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );
	virtual void					OnEnd( HeatseakerBot *me, Action< HeatseakerBot > *nextAction );

	virtual const char *GetName( void ) const	{ return "MissionDestroySentries"; };

private:
	CHandle< CObjectSentrygun > m_goalSentry;

	CObjectSentrygun *SelectSentryTarget( HeatseakerBot *me );
};


#endif // TF_BOT_MISSION_DESTROY_SENTRIES_H
