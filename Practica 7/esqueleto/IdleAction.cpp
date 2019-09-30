#include "stdafx.h"
#include "IdleAction.h"

Status IdleAction::update()
{
	m_Owner->SetImage(DragonSprite::IDLE);
	return Status::eSuccess;
}
