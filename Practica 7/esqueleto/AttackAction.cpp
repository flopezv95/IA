#include "stdafx.h"
#include "AttackAction.h"

void AttackAction::onEnter()
{
	
}

Status AttackAction::update()
{
	//printf("attack...");
	m_target->Damage(1);
	m_Owner->SetImage(DragonSprite::ATTACK);
	return Status::eSuccess;
}
