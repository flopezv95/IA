#include <stdafx.h>
#include "CanSeePlayerCondition.h"

 Status CanSeePlayerCondition::Check() const
{
	if (m_Target)
	{
		USVec2D PosPlayer(m_Target->GetLoc().mX, m_Target->GetLoc().mY);
		USVec2D PosOwner(m_Owner->GetLoc().mX, m_Owner->GetLoc().mY);
		return (PosOwner.Dist(PosPlayer) <= m_Owner->mMaxDisToSee && PosOwner.Dist(PosPlayer) > m_Owner->mMinDisToAttack) ? Status::eSuccess : Status::eFail;
	}
	else
	{ 
		return Status::eFail;
	}
}
