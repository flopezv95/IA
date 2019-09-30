#pragma once
#include "Behaviour.h"

class Character;

class Action: public Behavior
{
protected:
	virtual void onEnter() override {};
	virtual Status update() override { return Status::eInvalid; }
	virtual void onExit() override {};

};
