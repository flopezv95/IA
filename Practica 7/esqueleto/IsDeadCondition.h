#pragma once
#include "Condition.h"
#include "character.h"

class IsDeadCondition : public Condition
{
public:
	Status Check() const;
};
