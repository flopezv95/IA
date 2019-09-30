#pragma once
#include "Grupo.h"

class Sequence : public Group 
{
protected: 
	void onEnter(); 
	Status update();
	int m_CurrentChild;
public:
	virtual Status tick() override;
};