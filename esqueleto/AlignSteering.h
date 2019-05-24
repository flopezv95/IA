#ifndef  __ALIGNSTEERING__
#define  __ALIGNSTEERING__

#include <moaicore/MOAIEntity2D.h>

class Character;


class AlignSteering :public MOAIEntity2D
{
public:
	AlignSteering() {};
	void DrawDebug();
	float GetAceleration(Character * myCharacter, float targetPoint);
private:
	float  m_AngularVelocity;
    float  m_AngularAceleration;
	float m_wishRotation;
};

#endif
