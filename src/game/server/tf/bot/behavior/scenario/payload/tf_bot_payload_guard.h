//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_payload_guard.h
// Guard the payload and keep the attackers from getting near it
// Michael Booth, April 2010

#ifndef TF_BOT_PAYLOAD_GUARD_H
#define TF_BOT_PAYLOAD_GUARD_H

#include "Path/NextBotPathFollow.h"

class CTFBotPayloadGuard : public Action< HeatseakerBot >
{
public:
	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );
	virtual ActionResult< HeatseakerBot >	OnResume( HeatseakerBot *me, Action< HeatseakerBot > *interruptingAction );

	virtual EventDesiredResult< HeatseakerBot > OnStuck( HeatseakerBot *me );
	virtual EventDesiredResult< HeatseakerBot > OnMoveToSuccess( HeatseakerBot *me, const Path *path );
	virtual EventDesiredResult< HeatseakerBot > OnMoveToFailure( HeatseakerBot *me, const Path *path, MoveToFailureType reason );

	virtual EventDesiredResult< HeatseakerBot > OnTerritoryContested( HeatseakerBot *me, int territoryID );
	virtual EventDesiredResult< HeatseakerBot > OnTerritoryCaptured( HeatseakerBot *me, int territoryID );
	virtual EventDesiredResult< HeatseakerBot > OnTerritoryLost( HeatseakerBot *me, int territoryID );

	virtual QueryResultType	ShouldRetreat( const INextBot *me ) const;					// is it time to retreat?
	virtual QueryResultType ShouldHurry( const INextBot *me ) const;					// are we in a hurry?

	virtual const char *GetName( void ) const	{ return "PayloadGuard"; };

private:
	PathFollower m_path;
	CountdownTimer m_repathTimer;
	
	Vector m_vantagePoint;
	CountdownTimer m_vantagePointTimer;
	Vector FindVantagePoint( HeatseakerBot *me, CBaseEntity *cart );

	CountdownTimer m_moveToBlockTimer;

};

#endif // TF_BOT_PAYLOAD_GUARD_H
