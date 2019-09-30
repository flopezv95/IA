#ifndef __ALIGNTOMOVEMENTSTEERING__
#define __ALIGNTOMOVEMENTSTEERING__

#include <moaicore/MOAIEntity2D.h>

class Character;

class CAlignToMovementSteering : public MOAIEntity2D
{
public:
	virtual void DrawDebug();

	CAlignToMovementSteering();
	USVec3D getSteering(Character* ch, USVec3D targetPosition, float finalAngle = 0);

private:
	USVec3D mAcAndRot;

	USVec2D mVelDes;
	USVec2D mAc;

	float mRotDes;
	float mAcRot;
	float mWishRotation;
};

#endif