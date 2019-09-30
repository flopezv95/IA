#include "stdafx.h"
#include "DieAction.h"

Status DieAction::update()
{
	m_Owner->SetImage(DragonSprite::DIE);
	return Status::eSuccess;
}
