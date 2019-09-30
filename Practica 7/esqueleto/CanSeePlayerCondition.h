#pragma once
#include "Condition.h"
#include "character.h"

class CanSeePlayerCondition : public Condition
{
public:
	CanSeePlayerCondition(Character* newTarget) { m_Target = newTarget; }
	Status Check() const;
	
private:
	Character* m_Target;
};
