#include "stdafx.h"
#include "AlignSteering.h"
#include "character.h"

void AlignSteering::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 1.0f);
	gfxDevice.SetPenColor(1.0f, 1.0f, 0.0f, 1.0f);
	/*MOAIDraw::DrawLine(0.0f, 0.0f, m_AngularVelocity.mX, m_AngularVelocity.mY);
	gfxDevice.SetPenColor(1.0f, 0.0f, 1.0f, 1.0f);
	MOAIDraw::DrawLine(0.0f, 0.0f, m_AngularAceleration.mX, m_AngularAceleration.mY);*/
}

float AlignSteering::GetAceleration(Character * myCharacter, float targetPoint)
{
	if (targetPoint < 0)
	{
		targetPoint += 360;
	}
	m_AngularVelocity = targetPoint - myCharacter->GetRot();
	if ((myCharacter->GetRot() - targetPoint) <= myCharacter->GetParams().angular_arrive_radius)
	{
		if (targetPoint - myCharacter->GetRot() <= 180)
		{
			m_wishRotation = 0;
		}
		else
		{
			m_wishRotation = 360;
		}
		m_AngularVelocity *= myCharacter->GetParams().max_angular_velocity * ((targetPoint-m_wishRotation) / myCharacter->GetParams().angular_arrive_radius);
		m_AngularAceleration = m_AngularVelocity - myCharacter->GetAngularVelocity();
	}
	else
	{
		m_AngularVelocity *= myCharacter->GetParams().max_angular_velocity;
		m_AngularAceleration = m_AngularVelocity - myCharacter->GetAngularVelocity();
	}

	m_AngularAceleration *= myCharacter->GetParams().max_angular_acceleration;

	return m_AngularAceleration;
}
