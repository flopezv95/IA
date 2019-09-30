#pragma once
#include "Action.h"

class Transition;
class Condition;
class Character;

class State
{
public:
	State(std::string newName) { m_stateName = newName; }
	std::string GetStateName() { return m_stateName; }
	void OnEnter();
	void Update();
	void OnExit();
	std::vector<Transition*> &GetTransitions() { return m_Transitions; }
	void AddTransition(Condition* condition, State* targetState);
	void SetChOwner(Character* newChOwner) { chOwner = newChOwner; }
	//void SetEnterAction(Action* newEnterAction);
	//void SetExitAction(Action* newExitAction);
	void SetStateAction(Action* newStateAction);
	//Action* GetEnterAction() { return m_EnterAction; }
	//Action* GetExitAction() { return m_ExitAction; }
	Action* GetStateAction() { return m_StateAction; }

protected:
	Character* chOwner;

private:
	Action* m_StateAction;
	std::string m_stateName;
	//Action* m_ExitAction;
	//Action* m_EnterAction;
	std::vector<Transition*> m_Transitions;
};