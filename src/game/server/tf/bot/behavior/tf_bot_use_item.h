//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_use_item.h
// Equip and consume an item
// Michael Booth, July 2011

#ifndef TF_BOT_USE_ITEM_H
#define TF_BOT_USE_ITEM_H

class CTFBotUseItem : public Action< HeatseakerBot >
{
public:
	CTFBotUseItem( CTFWeaponBase *item );
	virtual ~CTFBotUseItem() { }

	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );
	virtual void					OnEnd( HeatseakerBot *me, Action< HeatseakerBot > *nextAction );

	virtual const char *GetName( void ) const	{ return "UseItem"; };

private:
	CHandle< CTFWeaponBase > m_item;
	CountdownTimer m_cooldownTimer;
};


#endif // TF_BOT_USE_ITEM_H
