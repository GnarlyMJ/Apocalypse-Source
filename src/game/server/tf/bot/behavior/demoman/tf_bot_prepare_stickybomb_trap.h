//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_prepare_stickybomb_trap.h
// Place stickybombs to create a deadly trap
// Michael Booth, July 2010

#ifndef TF_BOT_PREPARE_STICKYBOMB_TRAP_H
#define TF_BOT_PREPARE_STICKYBOMB_TRAP_H

class CTFBotPrepareStickybombTrap : public Action< HeatseakerBot >
{
public:
	CTFBotPrepareStickybombTrap( void );
	virtual ~CTFBotPrepareStickybombTrap( );

	static bool IsPossible( HeatseakerBot *me );	// Return true if this Action has what it needs to perform right now

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );
	virtual void					OnEnd( HeatseakerBot *me, Action< HeatseakerBot > *nextAction );

	virtual ActionResult< HeatseakerBot >	OnSuspend( HeatseakerBot *me, Action< HeatseakerBot > *interruptingAction );

	virtual EventDesiredResult< HeatseakerBot > OnInjured( HeatseakerBot *me, const CTakeDamageInfo &info );

	virtual QueryResultType			ShouldAttack( const INextBot *me, const CKnownEntity *them ) const;	// should we attack "them"?

	virtual const char *GetName( void ) const	{ return "PrepareStickybombTrap"; };

	struct BombTargetArea
	{
		CTFNavArea *m_area;
		int m_count;
	};

private:
	bool m_isFullReloadNeeded;

	CTFNavArea *m_myArea;

	CUtlVector< BombTargetArea > m_bombTargetAreaVector;
	void InitBombTargetAreas( HeatseakerBot *me );
	CountdownTimer m_launchWaitTimer;
};

#endif // TF_BOT_PREPARE_STICKYBOMB_TRAP_H
