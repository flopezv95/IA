#pragma once
#include <stdafx.h>
#include "character.h"
#include "Action.h"

class IdleAction : public Action
{
public:
	virtual Status update() override;

};