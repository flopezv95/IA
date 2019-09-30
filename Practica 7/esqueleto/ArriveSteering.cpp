
#include <stdafx.h>
#include "ArriveSteering.h"
#include "character.h"

CArriveSteering::CArriveSteering()
{

}

void CArriveSteering::DrawDebug()
{

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenWidth(1.0f);
	
	gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 1.0f);
	MOAIDraw::DrawLine(0, 0, mVelDes.mX, mVelDes.mY);

	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 1.0f);
	MOAIDraw::DrawLine(0, 0, mAc.mX, mAc.mY);
}

USVec2D CArriveSteering::getSteering(Character* ch, USVec3D target)
{
	mVelDes = USVec2D(target.mX - ch->GetLoc().mX, target.mY - ch->GetLoc().mY);

	if ((ch->GetLoc() - target).Length() > ch->getParams().arrive_radius)
	{
		mVelDes.Norm();
		mVelDes *= ch->getParams().max_velocity;

		mAc = (mVelDes - ch->GetLinearVelocity());

		mAc.Norm();
	} 
	else
	{
		mVelDes.Norm();
		mVelDes *= ch->getParams().max_velocity * ((ch->GetLoc() - target).Length() / ch->getParams().arrive_radius);

		mAc = (mVelDes - ch->GetLinearVelocity());

		mAc.Norm();
	}
	mAc *= ch->getParams().max_acceleration;

	return mAc;
}
