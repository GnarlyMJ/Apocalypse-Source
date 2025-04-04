//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_lurk.h
// Wait for victims
// Michael Booth, September 2011

#ifndef TF_BOT_SPY_LURK_H
#define TF_BOT_SPY_LURK_H

#include "Path/NextBotPathFollow.h"

class CTFBotSpyLurk : public Action< HeatseakerBot >
{
public:
	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual QueryResultType ShouldAttack( const INextBot *me, const CKnownEntity *them ) const;	// should we attack "them"?

	virtual const char *GetName( void ) const	{ return "SpyLurk"; };

private:
	CountdownTimer m_lurkTimer;
};


#endif // TF_BOT_SPY_LURK_H
