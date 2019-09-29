#pragma once
#pragma once
#include "Sequence.h"
#include <vector>

class Selector
{
protected:
	void onEnter();
	Status update();
	int m_CurrentSequence;
	typedef std::vector<Sequence*> Sequences;
	Sequences m_ChildrenSequence;

public:
	void AddSequence(Sequence * sequenceToAdd);
};