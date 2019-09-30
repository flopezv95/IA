#include "stdafx.h"
#include "Grupo.h"

void Group::AddNode(Behavior* behaviorToAdd)
{
	m_Children.push_back(behaviorToAdd);
}

void Group::SetOwner(Character* newOwner)
{
	m_Owner = newOwner;
	for (Behavior* chNode : m_Children)
	{
		chNode->SetOwner(newOwner);
	}
}
