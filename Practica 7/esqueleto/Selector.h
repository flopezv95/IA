#pragma once
#include "Sequence.h"
#include "Grupo.h"
#include <vector>

class Selector: public Group
{
protected:
	void onEnter();
	int m_CurrentSequence;
	typedef std::vector<Sequence*> Sequences;
	Sequences m_ChildrenSequence;

public:
	Status update();
	void AddSequence(Sequence * sequenceToAdd);
};