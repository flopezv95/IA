#include <stdafx.h>
#include "Behaviour.h"

Status Behavior::update()
{
	return m_Status;
}

void Behavior::onEnter()
{
	printf("Enter in the behavior");
}

void Behavior::onExit()
{
	printf("Exit from the behavior");
}

Behavior::Behavior(Character* owner)
{
	m_Owner = owner;
	m_Status = eInvalid;
}

Status Behavior::tick()
{
	if (m_Status == eInvalid) 
	{ 
		onEnter(); 
	}
	m_Status = update();
	if (m_Status != eRunning) 
	{ 
		onExit(); 
	} 
	return m_Status;
}
