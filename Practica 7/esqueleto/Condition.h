#pragma once
#include "Behaviour.h"

class Condition: public Behavior
{
public:
	virtual Status Check() const = 0;

protected: 
	virtual Status update() override 
	{ 
		return Check(); 
	}
};
