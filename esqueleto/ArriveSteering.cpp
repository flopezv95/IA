#include "stdafx.h"
#include "ArriveSteering.h"
#include "character.h"

void ArriveSteering::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 1.0f);
	gfxDevice.SetPenColor(1.0f, 1.0f, 0.0f, 1.0f);
	MOAIDraw::DrawLine(0.0f, 0.0f, m_Velocity.mX, m_Velocity.mY);
	gfxDevice.SetPenColor(1.0f, 0.0f, 1.0f, 1.0f);
	MOAIDraw::DrawLine(0.0f, 0.0f, m_Aceleration.mX, m_Aceleration.mY);
}

USVec2D ArriveSteering::GetAceleration(Character * myCharacter, USVec3D targetPoint)
{
	m_Velocity = USVec2D(targetPoint.mX - myCharacter->GetLoc().mX, targetPoint.mY - myCharacter->GetLoc().mY);
	
	if ((myCharacter->GetLoc() - targetPoint).Length() <= myCharacter->GetParams().arrive_radius)
	{
		m_Velocity.Norm();
		m_Velocity *= myCharacter->GetParams().max_velocity * ((myCharacter->GetLoc() - targetPoint).Length() / myCharacter->GetParams().arrive_radius);
		m_Aceleration = USVec2D(m_Velocity.mX - myCharacter->GetLinearVelocity().mX, m_Velocity.mY - myCharacter->GetLinearVelocity().mY);
		m_Aceleration.Norm();
	}
	else
	{
		m_Velocity.Norm();
		m_Velocity *= myCharacter->GetParams().max_velocity;
		m_Aceleration = USVec2D(m_Velocity.mX - myCharacter->GetLinearVelocity().mX, m_Velocity.mY - myCharacter->GetLinearVelocity().mY);
		m_Aceleration.Norm();		
	}

	m_Aceleration *= myCharacter->GetParams().max_acceleration;

	return m_Aceleration;
}
