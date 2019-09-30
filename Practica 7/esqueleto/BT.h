#pragma once
#include <vector>

class BTNode;
class Character;

class BT
{
public:
	BT(Character* newOwner) { m_BTOwner = newOwner; }
	void AddNodeToBT(BTNode* nodeToAdd) 
	{
		nodeToAdd->SetOwner(m_BTOwner);
		m_behaviourTree.push_back(nodeToAdd); 
	}
	void Update() {}

private:
	std::vector<BTNode*> m_behaviourTree;
	Character* m_BTOwner;
};
