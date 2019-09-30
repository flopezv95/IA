#include <stdafx.h>
#include "State.h"
#include "Transition.h"

void State::OnEnter()
{
	m_StateAction->Start();
}

void State::Update()
{
	m_StateAction->Update();
}

void State::OnExit()
{
	m_StateAction->End();
}

void State::AddTransition(Condition * condition, State * state)
{
	Transition * NewTransition = new Transition();
	NewTransition->SetCondition(condition);
	NewTransition->SetTransitionState(state);
	m_Transitions.push_back(NewTransition);
}

//void State::SetEnterAction(Action* newEnterAction)
//{
//	m_EnterAction = newEnterAction;
//	m_EnterAction->SetOwner(chOwner);
//}
//
//void State::SetExitAction(Action* newExitAction)
//{
//	m_ExitAction = newExitAction;
//	m_ExitAction->SetOwner(chOwner);
//}

void State::SetStateAction(Action* newStateAction)
{
	m_StateAction = newStateAction;
	m_StateAction->SetOwner(chOwner);
}
