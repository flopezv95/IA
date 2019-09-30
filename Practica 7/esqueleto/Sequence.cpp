#include "stdafx.h"
#include "Sequence.h"
#include "Selector.h"

void Sequence::onEnter()
{
	m_CurrentChild = 0;
}

Status Sequence::update()
{
	while (true) 
	{
		Status s = m_Children[m_CurrentChild]->tick();
		if (s != eSuccess)
		{ 
			return s; 
		} 
		++m_CurrentChild;
		if (m_CurrentChild == m_Children.size()) 
		{ 
			m_CurrentChild = 0;
			return eSuccess; 
		}
	} 
	return eInvalid;
}

Status Sequence::tick()
{
	if (m_Status == eInvalid)
	{
		onEnter();
	}
	m_Status = update();

	return m_Status;
}

