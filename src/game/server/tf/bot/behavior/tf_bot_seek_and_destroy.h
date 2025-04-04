//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_seek_and_destroy.h
// Roam the environment, attacking victims
// Michael Booth, January 2010

#ifndef TF_BOT_SEEK_AND_DESTROY_H
#define TF_BOT_SEEK_AND_DESTROY_H

#include "Path/NextBotChasePath.h"


//
// Roam around the map attacking enemies
//
class CTFBotSeekAndDestroy : public Action< HeatseakerBot >
{
public:
	CTFBotSeekAndDestroy( float duration = -1.0f );

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual ActionResult< HeatseakerBot >	OnResume( HeatseakerBot *me, Action< HeatseakerBot > *interruptingAction );

	virtual EventDesiredResult< HeatseakerBot > OnStuck( HeatseakerBot *me );
	virtual EventDesiredResult< HeatseakerBot > OnMoveToSuccess( HeatseakerBot *me, const Path *path );
	virtual EventDesiredResult< HeatseakerBot > OnMoveToFailure( HeatseakerBot *me, const Path *path, MoveToFailureType reason );

	virtual QueryResultType	ShouldRetreat( const INextBot *me ) const;					// is it time to retreat?
	virtual QueryResultType ShouldHurry( const INextBot *me ) const;					// are we in a hurry?

	virtual EventDesiredResult< HeatseakerBot > OnTerritoryCaptured( HeatseakerBot *me, int territoryID );
	virtual EventDesiredResult< HeatseakerBot > OnTerritoryLost( HeatseakerBot *me, int territoryID );
	virtual EventDesiredResult< HeatseakerBot > OnTerritoryContested( HeatseakerBot *me, int territoryID );

	virtual const char *GetName( void ) const	{ return "SeekAndDestroy"; };

private:
	CTFNavArea *m_goalArea;
	CTFNavArea *ChooseGoalArea( HeatseakerBot *me );
	bool m_isPointLocked;

	PathFollower m_path;
	CountdownTimer m_repathTimer;
	void RecomputeSeekPath( HeatseakerBot *me );

	CountdownTimer m_giveUpTimer;
};


#endif // TF_BOT_SEEK_AND_DESTROY_H
