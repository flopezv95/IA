#pragma once
#include <stdafx.h>
#include "character.h"
#include "Action.h"

class DieAction : public Action
{
public:
	virtual Status update() override;

};