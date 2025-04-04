//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_payload_block.h
// Prevent the other team from moving the cart
// Michael Booth, April 2010

#ifndef TF_BOT_PAYLOAD_BLOCK_H
#define TF_BOT_PAYLOAD_BLOCK_H

#include "Path/NextBotPathFollow.h"

class CTFBotPayloadBlock : public Action< HeatseakerBot >
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

	virtual const char *GetName( void ) const	{ return "PayloadBlock"; };

private:
	PathFollower m_path;
	CountdownTimer m_repathTimer;

	CountdownTimer m_giveUpTimer;
};

#endif // TF_BOT_PAYLOAD_BLOCK_H
