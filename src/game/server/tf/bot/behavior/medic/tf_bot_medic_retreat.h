//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_retreat.cpp
// Retreat towards our spawn to find another patient
// Michael Booth, May 2009

#ifndef TF_BOT_MEDIC_RETREAT_H
#define TF_BOT_MEDIC_RETREAT_H

#include "Path/NextBotChasePath.h"

class CTFBotMedicRetreat : public Action< HeatseakerBot >
{
public:
	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );
	virtual ActionResult< HeatseakerBot >	OnResume( HeatseakerBot *me, Action< HeatseakerBot > *interruptingAction );

	virtual EventDesiredResult< HeatseakerBot > OnStuck( HeatseakerBot *me );
	virtual EventDesiredResult< HeatseakerBot > OnMoveToFailure( HeatseakerBot *me, const Path *path, MoveToFailureType reason );
	virtual QueryResultType ShouldAttack( const INextBot *me, const CKnownEntity *them ) const;

	virtual const char *GetName( void ) const	{ return "Retreat"; };

private:
	PathFollower m_path;
	CountdownTimer m_lookAroundTimer;
};

#endif // TF_BOT_MEDIC_RETREAT_H
