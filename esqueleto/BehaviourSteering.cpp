#include "stdafx.h"
#include "BehaviourSteering.h"
#include "character.h"

void BehaviourSteering::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 1.0f);
	gfxDevice.SetPenColor(1.0f, 1.0f, 0.0f, 1.0f);
	/*MOAIDraw::DrawLine(0.0f, 0.0f, m_AngularVelocity.mX, m_AngularVelocity.mY);
	gfxDevice.SetPenColor(1.0f, 0.0f, 1.0f, 1.0f);
	MOAIDraw::DrawLine(0.0f, 0.0f, m_AngularAceleration.mX, m_AngularAceleration.mY);*/
}

USVec3D BehaviourSteering::GetAcelerations(Character * myCharacter, USVec3D targetPoint, float targetRotation)
{

	m_acelerationPosition = m_mySteeringArrive->GetAceleration(myCharacter, targetPoint);
	m_acelerations = USVec3D(m_acelerationPosition, m_mySteeringAlign->GetAceleration(myCharacter, targetRotation));

	return m_acelerations;
}