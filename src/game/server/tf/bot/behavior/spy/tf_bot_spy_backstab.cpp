//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_spy_backstab.cpp
// Chase behind a victim and backstab them
// Michael Booth, June 2010

#include "cbase.h"
#include "tf_player.h"
#include "bot/tf_bot.h"
#include "bot/behavior/spy/tf_bot_spy_backstab.h"

extern ConVar tf_bot_path_lookahead_range;

//---------------------------------------------------------------------------------------------
ActionResult< HeatseakerBot >	CTFBotSpyBackstab::OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction )
{
	return Continue();
}


//---------------------------------------------------------------------------------------------
ActionResult< HeatseakerBot >	CTFBotSpyBackstab::Update( HeatseakerBot *me, float interval )
{
	return Continue();
}


//---------------------------------------------------------------------------------------------
QueryResultType CTFBotSpyBackstab::ShouldAttack( const INextBot *me, const CKnownEntity *them ) const
{
	return ANSWER_NO;
}
