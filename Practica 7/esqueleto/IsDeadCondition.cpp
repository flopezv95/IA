#include "stdafx.h"
#include "IsDeadCondition.h"

Status IsDeadCondition::Check() const
{
	return (!m_Owner->IsAlive()) ? Status::eSuccess : Status::eFail;
}
