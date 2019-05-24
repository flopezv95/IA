#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>
#include "SeekSteering.h"
#include "BehaviourSteering.h"
#include <params.h>

Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
		RTTI_END
}

Character::~Character()
{

}

float Character::GetAngleBetweenVectors(USVec2D x1, USVec2D y1, USVec2D x2, USVec2D y2)
{
	mForwardVector = (x1 - y1);
	mVecPositionToGo = (x2 - y2);
	mForwardVector.Norm();
	mVecPositionToGo.Norm();
	float dotProduct = mVecPositionToGo.Dot(mForwardVector);
	float detProdcut = (mVecPositionToGo.mY * mForwardVector.mX) - (mVecPositionToGo.mX * mForwardVector.mY);

	return atan2(detProdcut, dotProduct) * (180 / PI);
}

void Character::OnStart()
{
	m_mySteering = new SeekSteering();
	m_mySteeringArrive = new ArriveSteering();
	m_mySteeringAlign = new AlignSteering();
	m_myBehaviourSteering = new BehaviourSteering();
    ReadParams("params_behaviour.xml", mParams);

	mAngle = GetAngleBetweenVectors(USVec2D(GetLoc().mX, GetLoc().mY), USVec2D(10.0f, GetLoc().mY), USVec2D(GetLoc().mX, GetLoc().mY), USVec2D(mParams.targetPosition.mX, mParams.targetPosition.mY));
	
}

void Character::OnStop()
{

}

void Character::OnUpdate(float step)
{
	/*
	acelerations = m_myBehaviourSteering->GetAcelerations(this, mParams.targetPosition, mAngle);

	mLinearVelocity.mX += acelerations.mX *step;
	mLinearVelocity.mY += acelerations.mY *step;

	const USVec2D position(((GetLoc().mX) + (mLinearVelocity.mX* step)), ((GetLoc().mY) + (mLinearVelocity.mY* step)));
	const USVec3D myPosition(position);
	SetLoc(myPosition);

	mAngularVelocity += acelerations.mZ * step;
	SetRot(GetRot() + mAngularVelocity * step);
	*/

	mAngularAceleration = m_mySteeringAlign->GetAceleration(this, mParams.targetRotation);
	mAngularVelocity += mAngularAceleration * step;
	SetRot(GetRot() + mAngularVelocity * step);
	/*
    //aceleration= m_mySteering->GetAceleration(this,mParams.targetPosition);
	aceleration = m_mySteeringArrive->GetAceleration(this, mParams.targetPosition);
	mLinearVelocity.mX += aceleration.mX *step;
	mLinearVelocity.mY += aceleration.mY *step;
	const USVec2D position (((GetLoc().mX) + (mLinearVelocity.mX* step)), ((GetLoc().mY) + (mLinearVelocity.mY* step)));
	const USVec3D myPosition(position);
	SetLoc(myPosition);
	*/
}

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 1.0f);
	MOAIDraw::DrawPoint(mParams.targetPosition.mX, mParams.targetPosition.mY);
	//m_mySteeringArrive->DrawDebug();
	//m_mySteering->DrawDebug();
}





// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(pX, pY);
	return 0;	
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}
	