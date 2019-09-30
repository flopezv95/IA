#include "stdafx.h"
#include "IsFarEnoughtCondition.h"

Status IsFarEnoughtCondition::Check() const
{
	if (m_Target)
	{
		USVec2D PosPlayer(m_Target->GetLoc().mX, m_Target->GetLoc().mY);
		USVec2D PosOwner(m_Owner->GetLoc().mX, m_Owner->GetLoc().mY);
		return (PosOwner.Dist(PosPlayer) > m_Owner->mMaxDisToSee) ? Status::eSuccess : Status::eFail;
	}
	else
	{
		return Status::eFail;
	}
}
