#pragma once
#include "Condition.h"

class AndCondition : public Condition
{
public:
	AndCondition(Condition* c1, Condition* c2) { m_c1 = c1; m_c1 = c1; }
	bool Check() const { return m_c1->Check() || m_c2->Check(); }
private:
	Condition* m_c1;
	Condition* m_c2;
};
