#ifndef __ALIGNSTEERING__
#define __ALIGNSTEERING__

#include <moaicore/MOAIEntity2D.h>

class Character;

class CAlignSteering : public MOAIEntity2D
{
public:
	virtual void DrawDebug();

	CAlignSteering();
	float getSteering(Character* ch, float finalAngle);

private:
	float mRotDes;
	float mAcRot;
	float mWishRotation;
};

#endif