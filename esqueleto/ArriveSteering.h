#ifndef  __ARRIVESTEERING__
#define  __ARRIVESTEERING__

#include <moaicore/MOAIEntity2D.h>

class Character;

class ArriveSteering :public MOAIEntity2D
{
public:
	ArriveSteering() {};
	void DrawDebug();
	USVec2D GetAceleration(Character * myCharacter, USVec3D targetPoint);
private:
	USVec2D  m_Velocity;
	USVec2D  m_Aceleration;
};

#endif
