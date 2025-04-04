//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_taunt.h
// Stand still and play a taunt animation
// Michael Booth, November 2009

#ifndef TF_BOT_TAUNT_H
#define TF_BOT_TAUNT_H


//-----------------------------------------------------------------------------
class CTFBotTaunt : public Action< HeatseakerBot >
{
public:
	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );

	virtual const char *GetName( void ) const	{ return "Taunt"; };

private:
	CountdownTimer m_tauntTimer;
	CountdownTimer m_tauntEndTimer;
	bool m_didTaunt;
};


#endif // TF_BOT_TAUNT_H
