//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_melee_attack.h
// Attack a threat with out melee weapon
// Michael Booth, February 2009

#ifndef TF_BOT_MELEE_ATTACK_H
#define TF_BOT_MELEE_ATTACK_H

#include "Path/NextBotChasePath.h"

class CTFBotMeleeAttack : public Action< HeatseakerBot >
{
public:
	CTFBotMeleeAttack( float giveUpRange = -1.0f );

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual const char *GetName( void ) const	{ return "MeleeAttack"; };

private:
	float m_giveUpRange;			// if non-negative and if threat is farther than this, give up our melee attack
	ChasePath m_path;
};

#endif // TF_BOT_MELEE_ATTACK_H
