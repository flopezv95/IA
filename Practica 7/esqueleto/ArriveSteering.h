#ifndef __ARRIVESTEERING__
#define __ARRIVESTEERING__

#include <moaicore/MOAIEntity2D.h>

class Character;

class CArriveSteering : public MOAIEntity2D
{
public:
	virtual void DrawDebug();

	CArriveSteering();
	USVec2D getSteering(Character* ch, USVec3D target);

private:
	USVec2D mVelDes;
	USVec2D mAc;

};

#endif