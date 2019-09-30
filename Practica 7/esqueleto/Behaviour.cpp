#include <stdafx.h>
#include "Behaviour.h"

void Behavior::onEnter()
{
}

Status Behavior::update()
{
	return Status::eSuccess;
}

void Behavior::onExit()
{
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
