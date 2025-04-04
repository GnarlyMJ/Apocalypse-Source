//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_get_ammo.h
// Pick up any nearby ammo
// Michael Booth, May 2009

#ifndef TF_BOT_GET_AMMO_H
#define TF_BOT_GET_AMMO_H

#include "tf_powerup.h"

class CTFBotGetAmmo : public Action< HeatseakerBot >
{
public:
	CTFBotGetAmmo( void );

	static bool IsPossible( HeatseakerBot *me );			// return true if this Action has what it needs to perform right now

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual EventDesiredResult< HeatseakerBot > OnContact( HeatseakerBot *me, CBaseEntity *other, CGameTrace *result = NULL );

	virtual EventDesiredResult< HeatseakerBot > OnStuck( HeatseakerBot *me );
	virtual EventDesiredResult< HeatseakerBot > OnMoveToSuccess( HeatseakerBot *me, const Path *path );
	virtual EventDesiredResult< HeatseakerBot > OnMoveToFailure( HeatseakerBot *me, const Path *path, MoveToFailureType reason );

	virtual QueryResultType ShouldHurry( const INextBot *me ) const;					// are we in a hurry?

	virtual const char *GetName( void ) const	{ return "GetAmmo"; };

private:
	PathFollower m_path;
	CHandle< CBaseEntity > m_ammo;
	bool m_isGoalDispenser;
};


#endif // TF_BOT_GET_AMMO_H
