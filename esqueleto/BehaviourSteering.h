#ifndef  __BEHAVIOURSTEERING__
#define  __BEHAVIOURSTEERING__

#include <moaicore/MOAIEntity2D.h>
#include "ArriveSteering.h"
#include "AlignSteering.h"

class Character;
class ArriveSteering;
class AlignSteering;

class BehaviourSteering :public MOAIEntity2D
{
public:
	BehaviourSteering() 
	{
		m_mySteeringArrive = new ArriveSteering();
		m_mySteeringAlign = new AlignSteering();
	};
	void DrawDebug();
	USVec3D GetAcelerations(Character * myCharacter, USVec3D targetPoint , float targetRotation);
private:
	ArriveSteering * m_mySteeringArrive;
	AlignSteering * m_mySteeringAlign;
	USVec2D  m_acelerationPosition;
	USVec3D m_acelerations;
};

#endif
