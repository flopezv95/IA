#pragma once
#include "Condition.h"
#include "character.h"

class IsFarEnoughtCondition : public Condition
{
public:
	IsFarEnoughtCondition(Character* newTarget) { m_Target = newTarget;  }
	Status Check() const;

private:
	Character* m_Target;
};