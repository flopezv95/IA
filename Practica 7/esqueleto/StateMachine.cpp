#include <stdafx.h>
#include "StateMachine.h"
#include "character.h"
#include "State.h"
#include "Transition.h"
#include "params.h"

StateMachine::StateMachine(Character* newChOwner)
{
	chOwner = newChOwner;
}

void StateMachine::AddNewState(State* newState)
{
	newState->SetChOwner(chOwner);
	for (State* iState : m_States)
	{
		if (iState == newState)
		{
			printf("ERROR: State already on array.");
			return;
		}
	}
	m_States.push_back(newState);
}

State * StateMachine::GetStateFromName(std::string stateName)
{
	for (State* st: m_States)
	{
		if (stateName == st->GetStateName())
		{
			return st;
		}
	}
	return nullptr;
}

void StateMachine::Load()
{
	
}

void StateMachine::Start()
{
	m_currentState = GetStateFromName("idle");
	if (m_currentState)
	{
		m_currentState->OnEnter();
	}
}

void StateMachine::Update()
{
	if (m_currentState)
	{
		m_currentState->Update();
		std::vector<Transition*> &transitions = m_currentState->GetTransitions();
		for (Transition* t : transitions)
		{
			if (t->CanTrigger())
			{
				m_currentState->OnExit();
				State* nextState = t->Trigger();
				nextState->OnEnter();
				m_currentState = nextState;
				return;
			}
		}
	}
}
