#pragma once
#include <stdafx.h>
#include "character.h"
#include "Action.h"

class AttackAction : public Action
{
public:
	AttackAction(Character* newTarget) { m_target = newTarget; }
	virtual void onEnter() override;
	virtual Status update() override;

private:
	Character* m_target;
};
