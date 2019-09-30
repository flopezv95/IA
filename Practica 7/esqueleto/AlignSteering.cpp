
#include <stdafx.h>
#include "AlignSteering.h"
#include "character.h"

CAlignSteering::CAlignSteering()
{

}

void CAlignSteering::DrawDebug()
{

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenWidth(1.0f);
	
	gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 1.0f);
	MOAIDraw::DrawPoint(0, mRotDes);

	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 1.0f);
	MOAIDraw::DrawPoint(0, mAcRot);
}

float CAlignSteering::getSteering(Character* ch, float finalAngle)
{
	mRotDes = finalAngle - ch->GetRot();

	if ((ch->GetRot() - finalAngle) > ch->getParams().angular_arrive_radius)
	{
		mRotDes *= ch->getParams().max_angular_velocity;

		mAcRot = mRotDes - ch->GetAngularVelocity();
	}
	else
	{
		mWishRotation = ((mRotDes <= 180) ? mRotDes : mRotDes - 360);

		mRotDes *= ch->getParams().max_angular_velocity * (mWishRotation / ch->getParams().angular_arrive_radius);

		mAcRot = mRotDes - ch->GetAngularVelocity();
	}
	mAcRot *= ch->getParams().max_angular_acceleration;

	return mAcRot;
}
