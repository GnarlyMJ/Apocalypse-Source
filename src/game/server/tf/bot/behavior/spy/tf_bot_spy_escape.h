//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_spy_escape.h
// Flee!
// Michael Booth, June 2010

#ifndef TF_BOT_SPY_ESCAPE_H
#define TF_BOT_SPY_ESCAPE_H

#include "Path/NextBotPathFollow.h"

class CTFBotSpyEscape : public Action< HeatseakerBot >
{
public:
	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual QueryResultType ShouldAttack( const INextBot *me, const CKnownEntity *them ) const;	// should we attack "them"?

	virtual const char *GetName( void ) const	{ return "SpyEscape"; };

private:
};

#endif // TF_BOT_SPY_ESCAPE_H
