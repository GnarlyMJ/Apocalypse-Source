//Heatseaker Locomotion File

#ifndef HEATSEAKER_LOCOMOTION_H
#define HEATSEAKER_LOCOMOTION_H

#include "NextBot/Player/NextBotPlayerLocomotion.h"

class HeatseakerLocomotion : public PlayerLocomotion
{
public:
	DECLARE_CLASS(HeatseakerLocomotion, PlayerLocomotion);

	HeatseakerLocomotion(INextBot* bot) : PlayerLocomotion(bot)
	{}

	virtual ~HeatseakerLocomotion() {}

	virtual void Update(void);

	virtual void Approach(const Vector& pos, float goalWeight = 1.0f);

	virtual float GetMaxJumpHeight(void) const;
	virtual float GetDeathDropHeight(void) const;

	virtual float GetRunSpeed(void) const;

	virtual bool IsAreaTraversable(const CNavArea* basearea) const;
	virtual bool IsEntityTraversable(CBaseEntity* obsticle, TraverseWhenType when = EVENTUALLY) const;

	virtual void Jump(void) OVERRIDE;

protected:
	virtual void AdjustPosture(const Vector $moveGoal) {}
};

inline float HeatseakerLocomotion::GetMaxJumpHeight(void) const
{
	return 0.0f;
}

#endif //