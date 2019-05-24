#include "stdafx.h"
#include "SeekSteering.h"
#include "character.h"

void SeekSteering::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 1.0f);
	gfxDevice.SetPenColor(1.0f, 1.0f, 0.0f, 1.0f);
	MOAIDraw::DrawLine(m_myCharacter->GetLoc().mX, m_myCharacter->GetLoc().mY, m_Velocity.mX, m_Velocity.mY);
	gfxDevice.SetPenColor(1.0f, 0.0f, 1.0f, 1.0f);
	MOAIDraw::DrawLine(m_myCharacter->GetLoc().mX, m_myCharacter->GetLoc().mY, m_Aceleration.mX, m_Aceleration.mY);
}

USVec2D SeekSteering::GetAceleration(Character * myCharacter, USVec3D targetPoint)
{
	m_myCharacter = myCharacter;
	m_Velocity = USVec2D(targetPoint.mX - myCharacter->GetLoc().mX, targetPoint.mY - myCharacter->GetLoc().mY);
	m_Velocity.Norm();
	m_Velocity *= myCharacter->GetParams().max_velocity;
	m_Aceleration = USVec2D(m_Velocity.mX - myCharacter->GetLinearVelocity().mX, m_Velocity.mY - myCharacter->GetLinearVelocity().mY);
	m_Aceleration.Norm();
	m_Aceleration *= myCharacter->GetParams().max_acceleration;
	return m_Aceleration;
}
