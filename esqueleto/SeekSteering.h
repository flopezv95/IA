#ifndef  __SEEKSTEERING__
#define  __SEEKSTEERING__
#include <moaicore/MOAIEntity2D.h>

class Character;

class SeekSteering : public MOAIEntity2D
{
public:
	SeekSteering() {};
	void DrawDebug();
	USVec2D GetAceleration(Character * myCharacter, USVec3D targetPoint);
private:
	USVec2D  m_Velocity;
	USVec2D  m_Aceleration;
	Character * m_myCharacter;
};

#endif

