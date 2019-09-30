#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <moaicore/MOAIEntity2D.h>
#include <params.h>
#include "State.h"

#define MAGONAME "mago"
#define DRAGONNAME "dragon"

// TODO: change_steering

//#define SEEK
//#define ARRIVE
//#define ALIGN
//#define ALIGNTOMOVEMENT
//#define PATHFINDING
//#define NOTMOVEMENT
//#define STATEMACHINE
#define BehaviorTreeAI

class CSeekSteering;
class CArriveSteering;
class CAlignSteering;
class CAlignToMovementSteering;
class CPathfindingSteering;
class StateMachine;
class Action;
class Sequence;
class Selector;
class BT;

enum DragonSprite
{
	IDLE = 0,
	ALARM = 1,
	ATTACK = 2,
	DIE = 3
};

class Character: public MOAIEntity2D
{
public:
    DECL_LUA_FACTORY(Character)
protected:
	virtual void OnStart();
	virtual void OnStop();

	float getAngleFromVectors(USVec2D v1d1, USVec2D v1d2, USVec2D v2d1, USVec2D v2d2);
	virtual void OnUpdate(float step);
	void OnUpdateSeek(float step);
	void OnUpdateArrive(float step);
	void OnUpdateAlign(float step);
	void OnUpdateAlignToMovement(float step);
	void OnUpdatePathfinding(float step);
	float angle;
public:
	virtual void DrawDebug();

	Character();
	~Character();
	
	void SetLinearVelocity(float x, float y) { mLinearVelocity.mX = x; mLinearVelocity.mY = y;}
	void SetAngularVelocity(float angle) { mAngularVelocity = angle;}
	void SetOwnerName(int ownerType);
	
	USVec2D GetLinearVelocity() const { return mLinearVelocity;}
	float GetAngularVelocity() const { return mAngularVelocity;}
	float mMaxDisToSee = 300.0f;
	float mMinDisToAttack = 100.0f;
	Params getParams();
	PathPoints getPathPoints();
	Params mParams;
private:
	std::string m_name = MAGONAME;
	int m_life = 1;
	USVec2D mLinearVelocity;
	float mAngularVelocity;
	PathPoints mPathPoints;
	StateMach mParamsStateMachine;
	StateMachine* mStateMachine;
	BTStruct mParamsBT;
	BT* mBehaviourTree;
	Selector* mainSelector;
	Character* mTarget;
	void UpdateTarget();

#ifdef SEEK
	CSeekSteering* mSteering;
#endif

#ifdef ARRIVE	
	CArriveSteering* mSteering;
#endif

#ifdef ALIGN
	CAlignSteering* mSteering;
#endif

#ifdef ALIGNTOMOVEMENT
	CAlignToMovementSteering* mSteering;
#endif

#ifdef PATHFINDING
	CPathfindingSteering* mSteering;
#endif

#ifdef STATEMACHINE
	CAlignToMovementSteering* mSteering;
#endif

#ifdef BehaviorTreeAI
	CAlignToMovementSteering* mSteering;
#endif

	// Lua configuration
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
	bool IsAlive() { return m_life > 0; }
	void Damage(int newDamage) { m_life -= newDamage; }

private:
	Action* CreateActionFromString(const char * nameOfFunction, Character* newTarget);
	Sequence* ReadSequenceFromString(NodeStruct nameOfFunction, Character* newTarget);
	void AddTransitionsToState(State* newState, StateStruct newST, Character* newTarget);
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
	static int _setOwnerName(lua_State* L);
};

#endif