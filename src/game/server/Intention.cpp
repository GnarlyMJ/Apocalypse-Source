#include "Heatseaker.h"
#include "cbase.h"

enum state
{
	Hunting = 0,
	Resting = 1,
	Tracking = 2
};

class HeatseakerAI : public Action< HeatseakerBot >
{
public:
	int curState = Hunting;
	int Hunger = 100000;
	//----------------------------------------------------------------------------------
	// OnStart is called once when the Action first becomes active
	virtual ActionResult< HeatseakerBot >	OnStart(HeatseakerBot* me, Action< HeatseakerBot >* priorAction)
	{
		// smooth out the bot's path following by moving toward a point farther down the path
		m_path.SetMinLookAheadDistance(300.0f);

		return Continue();
	}


	//----------------------------------------------------------------------------------
	// Update is called repeatedly (usually once per server frame) while the Action is active
	virtual ActionResult< HeatseakerBot >	Update(HeatseakerBot* me, float interval)
	{
		if (false)
		{
			curState = Tracking;
		}
		else if (Hunger < 9000 && curState != Resting)
		{
			curState = Resting;
		}
		else if (Hunger >= 70000)
		{
			curState = Hunting;
		}
		else if (curState == Resting)
		{
			Hunger += 50;
		}
		else if (m_path.IsValid() && !m_timer.IsElapsed() && curState == Hunting)
		{
			// PathFollower::Update() moves the bot along the path using the bot's ILocomotion and IBody interfaces
			m_path.Update(me);
			Hunger -= 10;
		}
		else
		{
			SelectNthAreaFunctor pick(RandomInt(0, TheNavMesh->GetNavAreaCount() - 1));
			TheNavMesh->ForAllAreas(pick);

			if (pick.m_area)
			{
				CSimpleBotPathCost cost(me);
				m_path.Compute(me, pick.m_area->GetCenter(), cost);
			}

			// follow this path for a random duration (or until we reach the end)
			m_timer.Start(RandomFloat(5.0f, 10.0f));
		}

		return Continue();
	}


	//----------------------------------------------------------------------------------
	// this is an event handler - many more are available (see declaration of Action< Actor > in NextBotBehavior.h)
	virtual EventDesiredResult< HeatseakerBot > OnStuck(HeatseakerBot* me)
	{
		// we are stuck trying to follow the current path - invalidate it so a new one is chosen
		m_path.Invalidate();

		return TryContinue();
	}


	virtual const char* GetName(void) const { return "Roam"; }		// return name of this action

private:
	PathFollower m_path;
	CountdownTimer m_timer;
};