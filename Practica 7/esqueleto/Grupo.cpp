#include "stdafx.h"
#include "Grupo.h"

void Group::AddBehaviour(Behavior * behaviorToAdd)
{
	m_Children.push_back(behaviorToAdd);
}
