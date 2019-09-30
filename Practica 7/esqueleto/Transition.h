#pragma once

#include "Condition.h"
class State;

class Transition
{
public:
	bool CanTrigger() const { return m_condition->Check(); }
	State* Trigger() { return m_targetState; }
	void SetCondition(Condition* condition) { m_condition = condition; }
	void SetTransitionState(State* state) { m_targetState = state; }
private:
	Condition* m_condition;
	State* m_targetState;
};
