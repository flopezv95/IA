#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <moaicore/MOAIEntity2D.h>
#include <params.h>

class SeekSteering;
class ArriveSteering;
class AlignSteering;
class BehaviourSteering;

class Character: public MOAIEntity2D
{
public:
    DECL_LUA_FACTORY(Character)
protected:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnUpdate(float step);
public:
	virtual void DrawDebug();

	Character();
	~Character();
	
	void SetLinearVelocity(float x, float y) { mLinearVelocity.mX = x; mLinearVelocity.mY = y;}
	void SetAngularVelocity(float angle) { mAngularVelocity = angle;}
	
	USVec2D GetLinearVelocity() const { return mLinearVelocity;}
	float GetAngularVelocity() const { return mAngularVelocity;}
	float GetAngleBetweenVectors(USVec2D x1, USVec2D y1, USVec2D x2, USVec2D y2);
	Params GetParams() { return mParams; }
private:
	SeekSteering * m_mySteering;
	ArriveSteering * m_mySteeringArrive;
	AlignSteering * m_mySteeringAlign;
	BehaviourSteering * m_myBehaviourSteering;
	USVec2D mLinearVelocity;
	USVec2D aceleration;
	USVec2D mForwardVector;
	USVec2D mVecPositionToGo;
	USVec3D acelerations;
	float mAngularVelocity;
	float mAngularAceleration;
	float mAngle;
	
	Params mParams;
	
	// Lua configuration
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
};

#endif