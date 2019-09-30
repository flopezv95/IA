#pragma once
#include "BTNode.h"
#include "Behaviour.h"
#include <vector>

class Group: public BTNode
{ 
protected: 

	typedef std::vector<Behavior*> Nodes; 
	Nodes m_Children; 

public:
	void AddNode(Behavior* nodeToAdd);
	virtual void SetOwner(Character* newOwner) override;
};