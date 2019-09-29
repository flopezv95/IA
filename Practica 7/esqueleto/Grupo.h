#pragma once
#include "Behaviour.h"
#include <vector>

class Group : public Behavior 
{ 
protected: 

	typedef std::vector<Behavior*> Behaviors; 
	Behaviors m_Children; 

public:
	void AddBehaviour(Behavior * behaviorToAdd);
};