#include "stdafx.h"
#include<windows.h>
#include "AlertedAction.h"

AlertedAction::AlertedAction(Character * newTarget)
{
	m_Target = newTarget;
}

void AlertedAction::onEnter()
{
	if (m_Owner && m_Target)
	{
		m_Owner->mParams.targetPosition = USVec2D(m_Target->GetLoc().mX, m_Target->GetLoc().mY);
	}
}

Status AlertedAction::update()
{
	SetAlarmSprite();
	m_Owner->mParams.targetPosition = USVec2D(m_Target->GetLoc().mX, m_Target->GetLoc().mY);
	//printf("moving...");
	return Status::eSuccess;
}

void AlertedAction::SetAlarmSprite()
{
	m_Owner->SetImage(DragonSprite::ALARM);
}
