//========= Copyright Valve Corporation, All rights reserved. ============//
// tf_bot_medic_heal.h
// Heal a teammate
// Michael Booth, February 2009

#ifndef TF_BOT_MEDIC_HEAL_H
#define TF_BOT_MEDIC_HEAL_H

#include "Path/NextBotChasePath.h"

class CWeaponMedigun;

class CTFBotMedicHeal : public Action< HeatseakerBot >
{
public:
	virtual ActionResult< HeatseakerBot >	OnStart( HeatseakerBot *me, Action< HeatseakerBot > *priorAction );
	virtual ActionResult< HeatseakerBot >	Update( HeatseakerBot *me, float interval );
	virtual ActionResult< HeatseakerBot >	OnResume( HeatseakerBot *me, Action< HeatseakerBot > *interruptingAction );

	virtual EventDesiredResult< HeatseakerBot > OnStuck( HeatseakerBot *me );
	virtual EventDesiredResult< HeatseakerBot > OnMoveToSuccess( HeatseakerBot *me, const Path *path );
	virtual EventDesiredResult< HeatseakerBot > OnMoveToFailure( HeatseakerBot *me, const Path *path, MoveToFailureType reason );
	virtual EventDesiredResult< HeatseakerBot > OnActorEmoted( HeatseakerBot *me, CBaseCombatCharacter *emoter, int emote );

	virtual QueryResultType ShouldHurry( const INextBot *me ) const;					// are we in a hurry?
	virtual QueryResultType ShouldAttack( const INextBot *me, const CKnownEntity *them ) const;	// should we attack "them"?
	virtual QueryResultType ShouldRetreat( const INextBot *bot ) const;

	virtual const char *GetName( void ) const	{ return "Heal"; };

private:
	ChasePath m_chasePath;

	CTFPlayer *SelectPatient( HeatseakerBot *me, CTFPlayer *current );
	CountdownTimer m_changePatientTimer;

	CountdownTimer m_delayUberTimer;

	CHandle< CTFPlayer > m_patient;
	Vector m_patientAnchorPos;							// a spot where the patient was, to track if they are moving
	CountdownTimer m_isPatientRunningTimer;
	bool IsPatientRunning( void ) const;

	bool IsStable( CTFPlayer *patient ) const;			// return true if the given patient is healthy and safe for now

	CTFNavArea *FindCoverArea( HeatseakerBot *me );
	CTFNavArea *m_coverArea;
	CountdownTimer m_coverTimer;
	PathFollower m_coverPath;

	void ComputeFollowPosition( HeatseakerBot *me );
	Vector m_followGoal;

	bool IsVisibleToEnemy( HeatseakerBot *me, const Vector &where ) const;

	bool IsReadyToDeployUber( const CWeaponMedigun* pMedigun ) const;

	bool IsGoodUberTarget( CTFPlayer *who ) const;

	bool CanDeployUber( HeatseakerBot *me, const CWeaponMedigun* pMedigun ) const;
};

inline bool CTFBotMedicHeal::IsPatientRunning( void ) const
{
	return m_isPatientRunningTimer.IsElapsed() ? false : true;
}


#endif // TF_BOT_MEDIC_HEAL_H
