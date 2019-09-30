#ifndef __PATHFINDINGSTEERING__
#define __PATHFINDINGSTEERING__

#include <moaicore/MOAIEntity2D.h>

class Character;

class CPathfindingSteering : public MOAIEntity2D
{
public:
	virtual void DrawDebug();

	CPathfindingSteering(Character* ch);
	int getClosestPointOnPath();
	USVec3D getSteering(USVec3D targetPosition, float finalAngle);

private:
	Character* mch;
	USVec3D mAcAndRot;

	USVec2D mVelDes;
	USVec2D mAc;

	float mRotDes;
	float mAcRot;
	float mWishRotation;
};

#endif