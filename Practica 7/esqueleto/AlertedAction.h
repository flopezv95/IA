#pragma once

#include <stdafx.h>
#include "character.h"
#include "Action.h"

class AlertedAction : public Action
{
public:
	AlertedAction(Character* newTarget);

protected:
	virtual void onEnter() override;
	virtual Status update() override;

private:
	Character* m_Target;
	void SetAlarmSprite();
};
