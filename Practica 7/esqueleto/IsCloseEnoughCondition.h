#pragma once
#include "Condition.h"
#include "character.h"

class IsCloseEnoughCondition : public Condition
{
public:
	IsCloseEnoughCondition(Character* newTarget) { m_Target = newTarget; }
	Status Check() const;

private:
	Character* m_Target;
};
