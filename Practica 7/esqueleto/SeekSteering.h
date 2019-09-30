#ifndef __SEEKSTEERING__
#define __SEEKSTEERING__

#include <moaicore/MOAIEntity2D.h>

class Character;

class CSeekSteering : public MOAIEntity2D
{
public:
	virtual void DrawDebug();

	CSeekSteering();
	USVec2D getSteering(Character* ch, USVec3D target);

private:
	USVec2D mVelDes;
	USVec2D mAc;

};

#endif