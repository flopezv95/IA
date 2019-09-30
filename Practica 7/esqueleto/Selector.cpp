#include "stdafx.h"
#include "Sequence.h"
#include "Selector.h"

void Selector::onEnter()
{
	m_CurrentSequence = 0;
}

Status Selector::update()
{
	while (true)
	{
		Status s = m_ChildrenSequence[m_CurrentSequence]->tick();
		if (s == eSuccess)
		{
			return s;
		}
		++m_CurrentSequence;
		if (m_CurrentSequence == m_ChildrenSequence.size())
		{
			m_CurrentSequence = 0;
			return eSuccess;
		}
	}
	return eInvalid;
}

void Selector::AddSequence(Sequence * sequenceToAdd)
{
	m_ChildrenSequence.push_back(sequenceToAdd);
}
