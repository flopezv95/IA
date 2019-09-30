#pragma once
#include "BTNode.h"
class Character;

class Behavior: public BTNode
{ 
protected:
	virtual Status update();
	virtual void onEnter(); 
	virtual void onExit(); 

public:
	virtual Status tick() override;
};