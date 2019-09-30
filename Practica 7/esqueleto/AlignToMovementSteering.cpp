
#include <stdafx.h>
#include "AlignToMovementSteering.h"
#include "character.h"

CAlignToMovementSteering::CAlignToMovementSteering()
{

}

void CAlignToMovementSteering::DrawDebug()
{

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenWidth(1.0f);
	
	gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 1.0f);
	MOAIDraw::DrawPoint(0, mRotDes);

	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 1.0f);
	MOAIDraw::DrawPoint(0, mAcRot);
}

USVec3D CAlignToMovementSteering::getSteering(Character* ch, USVec3D targetPosition, float finalAngle)
{
	// MOV
	mVelDes = USVec2D(targetPosition.mX - ch->GetLoc().mX, targetPosition.mY - ch->GetLoc().mY);

	if ((ch->GetLoc() - targetPosition).Length() > ch->getParams().arrive_radius)
	{
		mVelDes.Norm();
		mVelDes *= ch->getParams().max_velocity;

		mAc = (mVelDes - ch->GetLinearVelocity());

		mAc.Norm();
	}
	else
	{
		mVelDes.Norm();
		mVelDes *= ch->getParams().max_velocity * ((ch->GetLoc() - targetPosition).Length() / ch->getParams().arrive_radius);

		mAc = (mVelDes - ch->GetLinearVelocity());

		mAc.Norm();
	}
	mAc *= ch->getParams().max_acceleration;

	// ROT
	
	if (finalAngle < 0)
		finalAngle += 360;

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

	mAcAndRot = USVec3D(mAc.mX, mAc.mY, mAcRot);

	return mAcAndRot;
}
