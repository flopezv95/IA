
#include <stdafx.h>
#include "SeekSteering.h"
#include "character.h"

CSeekSteering::CSeekSteering() 
{

}

void CSeekSteering::DrawDebug()
{

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenWidth(1.0f);
	
	gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 1.0f);
	MOAIDraw::DrawLine(0, 0, mVelDes.mX, mVelDes.mY);

	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 1.0f);
	MOAIDraw::DrawLine(0, 0, mAc.mX, mAc.mY);
}

USVec2D CSeekSteering::getSteering(Character* ch, USVec3D target)
{
	mVelDes = USVec2D(target.mX - ch->GetLoc().mX, target.mY - ch->GetLoc().mY);

	mVelDes.Norm();
	mVelDes *= ch->getParams().max_velocity;

	mAc = (mVelDes - ch->GetLinearVelocity());

	mAc.Norm();
	mAc *= ch->getParams().max_acceleration;

	return mAc;
}
