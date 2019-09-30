
#include <stdafx.h>
#include "PathfindingSteering.h"
#include "character.h"
#include <stdlib.h>

CPathfindingSteering::CPathfindingSteering(Character* ch)
{
	mch = ch;
}

void CPathfindingSteering::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 0.0f);
	gfxDevice.SetPenWidth(4.0f);
	for (unsigned int i = 0; i < mch->getPathPoints().mPathPoints.size() - 1; ++i)
	{
		MOAIDraw::DrawLine(mch->getPathPoints().mPathPoints[i], mch->getPathPoints().mPathPoints[i+1]);
	}
}

int CPathfindingSteering::getClosestPointOnPath()
{
	float minDis = 9999.0f;
	//USVec2D ret(.0f, .0f);
	int ret = 0;
	for (unsigned int i = 0; i < mch->getPathPoints().mPathPoints.size() - 1; ++i)
	{
		float tempDis = (mch->GetLoc() - mch->getPathPoints().mPathPoints[i]).Length();
		if (tempDis > 1.0f && tempDis < minDis)
		{
			minDis = tempDis;
			ret = i + 1;// mch->getPathPoints().mPathPoints[i + 1];
		}
	}
	return ret;
}

USVec3D CPathfindingSteering::getSteering(USVec3D targetPosition, float finalAngle)
{
	// MOV
	mVelDes = USVec2D(targetPosition.mX - mch->GetLoc().mX, targetPosition.mY - mch->GetLoc().mY);

	if ((mch->GetLoc() - targetPosition).Length() > mch->getParams().arrive_radius)
	{
		mVelDes.Norm();
		mVelDes *= mch->getParams().max_velocity;

		mAc = (mVelDes - mch->GetLinearVelocity());

		mAc.Norm();
	}
	else
	{
		mVelDes.Norm();
		mVelDes *= mch->getParams().max_velocity * ((mch->GetLoc() - targetPosition).Length() / mch->getParams().arrive_radius);

		mAc = (mVelDes - mch->GetLinearVelocity());

		mAc.Norm();
	}
	mAc *= mch->getParams().max_acceleration;

	// ROT

	if (finalAngle < 0)
		finalAngle += 360;

	mRotDes = finalAngle - mch->GetRot();

	if ((mch->GetRot() - finalAngle) > mch->getParams().angular_arrive_radius)
	{
		mRotDes *= mch->getParams().max_angular_velocity;

		mAcRot = mRotDes - mch->GetAngularVelocity();
	}
	else
	{

		mWishRotation = ((mRotDes <= 180) ? mRotDes : mRotDes - 360);

		mRotDes *= mch->getParams().max_angular_velocity * (mWishRotation / mch->getParams().angular_arrive_radius);

		mAcRot = mRotDes - mch->GetAngularVelocity();
	}
	mAcRot *= mch->getParams().max_angular_acceleration;

	mAcAndRot = USVec3D(mAc.mX, mAc.mY, mAcRot);

	return mAcAndRot;
}
