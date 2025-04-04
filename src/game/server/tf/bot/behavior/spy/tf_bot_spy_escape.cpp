//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_spy_escape.cpp
// Flee!
// Michael Booth, June 2010

#include "cbase.h"
#include "tf_player.h"
#include "bot/tf_bot.h"
#include "bot/behavior/spy/tf_bot_spy_escape.h"

extern ConVar tf_bot_path_lookahead_range;

//---------------------------------------------------------------------------------------------
ActionResult< HeatseakerBot >	CTFBotSpyEscape::OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction )
{
	return Continue();
}


//---------------------------------------------------------------------------------------------
ActionResult< HeatseakerBot >	CTFBotSpyEscape::Update( HeatseakerBot *me, float interval )
{
	return Continue();
}


//---------------------------------------------------------------------------------------------
QueryResultType CTFBotSpyEscape::ShouldAttack( const INextBot *me, const CKnownEntity *them ) const
{
	return ANSWER_NO;
}
