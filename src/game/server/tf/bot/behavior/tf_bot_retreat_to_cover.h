//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_retreat_to_cover.h
// Retreat to local cover from known threats
// Michael Booth, June 2009

#ifndef TF_BOT_RETREAT_TO_COVER_H
#define TF_BOT_RETREAT_TO_COVER_H

class CTFBotRetreatToCover : public Action< HeatseakerBot >
{
public:
	CTFBotRetreatToCover( float hideDuration = -1.0f );
	CTFBotRetreatToCover( Action< HeatseakerBot > *actionToChangeToOnceCoverReached );

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual EventDesiredResult< HeatseakerBot > OnStuck( HeatseakerBot *me );
	virtual EventDesiredResult< HeatseakerBot > OnMoveToSuccess( HeatseakerBot *me, const Path *path );
	virtual EventDesiredResult< HeatseakerBot > OnMoveToFailure( HeatseakerBot *me, const Path *path, MoveToFailureType reason );

	virtual QueryResultType ShouldHurry( const INextBot *me ) const;					// are we in a hurry?

	virtual const char *GetName( void ) const	{ return "RetreatToCover"; };

private:
	float m_hideDuration;
	Action< HeatseakerBot > *m_actionToChangeToOnceCoverReached;

	PathFollower m_path;
	CountdownTimer m_repathTimer;

	CTFNavArea *m_coverArea;
	CountdownTimer m_waitInCoverTimer;

	CTFNavArea *FindCoverArea( HeatseakerBot *me );
};



#endif // TF_BOT_RETREAT_TO_COVER_H
