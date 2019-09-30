#pragma once

#include <iostream>
#include <vector>

class Character;
class State;

class StateMachine
{
public:
	StateMachine(Character* newChOwner);
	void AddNewState(State* newState);
	State* GetStateFromName(std::string stateName);
	std::vector<State*> GetAllStates() { return m_States; }
	void Load();
	void Start();
	void Update();
	Character* GetChOwner() { return chOwner; }

private:
	std::vector<State*> m_States;
	State* m_currentState;
	Character* chOwner;
};