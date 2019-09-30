#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>

#include "SeekSteering.h"
#include "ArriveSteering.h"
#include "AlignSteering.h"
#include "AlignToMovementSteering.h"
#include "PathfindingSteering.h"
#include "State.h"
#include "IdleAction.h"
#include "AlertedAction.h"
#include "AttackAction.h"
#include "DieAction.h"
#include <params.h>
#include "CanSeePlayerCondition.h"
#include "Transition.h"
#include "IsCloseEnoughCondition.h"
#include "IsDeadCondition.h"
#include "World.h"
#include "IsFarEnoughtCondition.h"
#include "BT.h"
#include "Grupo.h"
#include "Selector.h"
#include "Behaviour.h"

#ifdef SEEK
#define NAME_PARAMS_FILE "paramsSeek.xml"
#endif

#ifdef ARRIVE	
#define NAME_PARAMS_FILE "paramsArrive.xml"
#endif

#ifdef ALIGN
#define NAME_PARAMS_FILE "paramsAlign.xml"
#endif

#if defined ALIGNTOMOVEMENT || defined STATEMACHINE || defined BehaviorTreeAI
#define NAME_PARAMS_FILE "paramsAlignToMovement.xml"
#endif

#ifdef PATHFINDING
#define NAME_PARAMS_FILE "paramsPathfinding.xml"
#define NAME_PATH_POINTS_FILE "path.xml"
#endif

Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
	RTTI_END
}

Character::~Character()
{
}

void Character::SetOwnerName(int ownerType)
{
	if (ownerType == 0)
	{
		m_name = MAGONAME;
	}
	else
	{
		m_name = DRAGONNAME;
	}
}

void Character::OnStart()
{
	World::AddToWorld(this);
#ifdef SEEK
	mSteering = new CSeekSteering();
#endif

#ifdef ARRIVE	
	mSteering = new CArriveSteering();
#endif

#ifdef ALIGN
	mSteering = new CAlignSteering();
#endif

#ifdef ALIGNTOMOVEMENT
	mSteering = new CAlignToMovementSteering();
#endif
	
#ifdef PATHFINDING
	mSteering = new CPathfindingSteering(this);
	ReadPathPoints(NAME_PATH_POINTS_FILE, mPathPoints);
	SetLoc(mPathPoints.mPathPoints[0]);
#endif

#ifdef STATEMACHINE
	mSteering = new CAlignToMovementSteering();
	angle = getAngleFromVectors(USVec2D(GetLoc().mX, GetLoc().mY), USVec2D(10.0f, GetLoc().mY), USVec2D(GetLoc().mX, GetLoc().mY), USVec2D(mParams.targetPosition.mX, mParams.targetPosition.mY));
	if (m_name != MAGONAME)
	{
		ReadStateMachineParams("statesMachine.xml", mParamsStateMachine);

		mStateMachine = new StateMachine(this);
		UpdateTarget();

		for (StateStruct St : mParamsStateMachine.States)
		{
			State* newState = new State(St.StateName);
			mStateMachine->AddNewState(newState);
			Action* newAction = CreateActionFromString((St.Action).c_str(), mTarget);
			newState->SetStateAction(newAction);
		}
		for (StateStruct St : mParamsStateMachine.States)
		{
			for (State* stateToSaveTrans: mStateMachine->GetAllStates())
			{
				if (St.StateName == stateToSaveTrans->GetStateName())
				{
					AddTransitionsToState(stateToSaveTrans, St, mTarget);
				}
			}
		}
		mStateMachine->Start();
	}
#endif

#ifdef BehaviorTreeAI
	mSteering = new CAlignToMovementSteering();
	angle = getAngleFromVectors(USVec2D(GetLoc().mX, GetLoc().mY), USVec2D(10.0f, GetLoc().mY), USVec2D(GetLoc().mX, GetLoc().mY), USVec2D(mParams.targetPosition.mX, mParams.targetPosition.mY));
	if (m_name != MAGONAME)
	{
		ReadBTParams("BehaviourTree.xml", mParamsBT);

		mBehaviourTree = new BT(this);
		UpdateTarget();

		mainSelector = new Selector();

		for (NodeStruct St : mParamsBT.Nodes)
		{
			if (St.Type == "sequence")
			{

				Sequence* newSequence = ReadSequenceFromString(St, mTarget);
				mBehaviourTree->AddNodeToBT(newSequence);
				mainSelector->AddSequence(newSequence);
			}
		}
		//mBehaviourTree->AddNodeToBT(mainSelector);
		//mainSelector->update();
	}
#endif

#ifdef NOTMOVEMENT	
	//ReadParams(NAME_PARAMS_FILE, mParams);
#endif
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

#ifdef STATEMACHINE
void Character::AddTransitionsToState(State* newState, StateStruct newST, Character* target)
{
	for (std::map<std::string, std::string>::iterator it = newST.Transitions.begin(); it != newST.Transitions.end(); ++it)
	{
		Condition* newCond;
		switch (str2int((it->first).c_str()))
		{
			case static_cast<uint32_t>(str2int("canseeplayer")) :
			{
				newCond = new CanSeePlayerCondition(target);
				break;
			}
			case static_cast<uint32_t>(str2int("iscloseenough")) :
			{
				newCond = new IsCloseEnoughCondition(target);
				break;
			}
			case static_cast<uint32_t>(str2int("isfarenought")) :
			{
				newCond = new IsFarEnoughtCondition(target);
				break;
			}
			case static_cast<uint32_t>(str2int("isdead")) :
			{
				newCond = new IsDeadCondition();
				break;
			}
		}
		newState->AddTransition(newCond, mStateMachine->GetStateFromName(it->second));
	}
}
#endif

Action* Character::CreateActionFromString(const char * nameOfFunction, Character* newTarget)
{
	Action* actionToReturn = nullptr;
	switch (str2int(nameOfFunction))
	{
		case static_cast<uint32_t>(str2int("idleaction")):
			actionToReturn = new IdleAction();
			break;
		case static_cast<uint32_t>(str2int("alertedaction")):
			actionToReturn = new AlertedAction(newTarget);
			break;
		case static_cast<uint32_t>(str2int("attackaction")):
			actionToReturn = new AttackAction(newTarget);
			break;
		case static_cast<uint32_t>(str2int("dieaction")):
			actionToReturn = new DieAction();
			break;
	}
	return actionToReturn;
}

Sequence* Character::ReadSequenceFromString(NodeStruct nameOfSequence, Character* newTarget)
{
	Sequence* sequenceToReturn = new Sequence();
	for (NodeStruct nSt : nameOfSequence.ChildNodes)
	{
		Behavior* behaviurToAdd = nullptr;
		switch (str2int((nSt.Type).c_str()))
		{
			case static_cast<uint32_t>(str2int("idleaction")) :
			{	
				behaviurToAdd = new IdleAction();
				break;
			}
			case static_cast<uint32_t>(str2int("alertedaction")) :
			{
				behaviurToAdd = new AlertedAction(newTarget);
				break;
			}
			case static_cast<uint32_t>(str2int("attackaction")) :
			{
				behaviurToAdd = new AttackAction(newTarget);
				break;
			}
			case static_cast<uint32_t>(str2int("dieaction")) :
			{
				behaviurToAdd = new DieAction();
				break;
			}
			case static_cast<uint32_t>(str2int("isfarenoughtcondition")) :
			{
				behaviurToAdd = new IsFarEnoughtCondition(newTarget);
				break;
			}
			case static_cast<uint32_t>(str2int("iscloseenoughcondition")) :
			{
				behaviurToAdd = new IsCloseEnoughCondition(newTarget);
				break;
			}
			case static_cast<uint32_t>(str2int("canseeplayercondition")) :
			{
				behaviurToAdd = new CanSeePlayerCondition(newTarget);
				break;
			}
			case static_cast<uint32_t>(str2int("diecondition")) :
			{
				behaviurToAdd = new IsDeadCondition();
				break;
			}
		}
		sequenceToReturn->AddNode(behaviurToAdd);
	}
	return sequenceToReturn;
}

void Character::OnStop()
{

}

Params Character::getParams()
{
	return mParams;
}

PathPoints Character::getPathPoints()
{
	return mPathPoints;
}

void Character::UpdateTarget()
{
	for (Character* TargetToUse : World::Characters)
	{
		if (TargetToUse != this && TargetToUse != nullptr)
		{
			mTarget = TargetToUse;
		}
	}
}

float Character::getAngleFromVectors(USVec2D v1d1, USVec2D v1d2, USVec2D v2d1, USVec2D v2d2)
{
	USVec2D v1 = v1d2 - v1d1;
	USVec2D v2 = v2d2 - v2d1;
	v1.Norm();
	v2.Norm();
	float dot = v2.Dot(v1);
	float det = v1.mX * v2.mY - v1.mY * v2.mX;
	return static_cast<float>(atan2(det, dot) * (180 / PI));
}

void Character::OnUpdate(float step)
{
#ifdef SEEK
	OnUpdateSeek(step);
#endif

#ifdef ARRIVE	
	OnUpdateArrive(step);
#endif

#ifdef ALIGN
	OnUpdateAlign(step);
#endif

#if defined ALIGNTOMOVEMENT || defined STATEMACHINE || defined BehaviorTreeAI
	if (m_name != MAGONAME)
	{
		OnUpdateAlignToMovement(step);
	}
#endif	

#ifdef PATHFINDING
	OnUpdatePathfinding(step);
#endif	
	UpdateTarget();

	if (m_name != MAGONAME)
	{
#ifdef BehaviorTreeAI
		mainSelector->update();
#endif
#ifdef STATEMACHINE
		mStateMachine->Update();
#endif
	}
}

#ifdef SEEK
void Character::OnUpdateSeek(float step)
{

	USVec2D vec2_ac = mSteering->getSteering(this, mParams.targetPosition);

	mLinearVelocity.mX += step * vec2_ac.mX;
	mLinearVelocity.mY += step * vec2_ac.mY;

	const USVec2D newPos(GetLoc().mX + step * mLinearVelocity.mX, GetLoc().mY + step * mLinearVelocity.mY);
	const USVec3D newLoc(newPos, GetLoc().mZ);
	SetLoc(newLoc);
}
#endif

#ifdef ARRIVE
void Character::OnUpdateArrive(float step)
{
	USVec2D vec2_ac = mSteering->getSteering(this, mParams.targetPosition);

	mLinearVelocity.mX += step * vec2_ac.mX;
	mLinearVelocity.mY += step * vec2_ac.mY;

	const USVec2D newPos(GetLoc().mX + step * mLinearVelocity.mX, GetLoc().mY + step * mLinearVelocity.mY);
	const USVec3D newLoc(newPos, GetLoc().mZ);
	SetLoc(newLoc);
}
#endif

#ifdef ALIGN
void Character::OnUpdateAlign(float step)
{
	float rot = mSteering->getSteering(this, angle);
	mAngularVelocity += step * rot;

	const float newRot = GetRot() + step * mAngularVelocity;
	SetRot(newRot);
}
#endif

#if defined ALIGNTOMOVEMENT || defined STATEMACHINE || defined BehaviorTreeAI
void Character::OnUpdateAlignToMovement(float step)
{
	USVec3D vec3_acAndRot = mSteering->getSteering(this, mParams.targetPosition, angle);

	USVec2D vec2_ac = USVec2D(vec3_acAndRot.mX, vec3_acAndRot.mY);

	mLinearVelocity.mX += step * vec2_ac.mX;
	mLinearVelocity.mY += step * vec2_ac.mY;

	const USVec2D newPos(GetLoc().mX + step * mLinearVelocity.mX, GetLoc().mY + step * mLinearVelocity.mY);
	const USVec3D newLoc(newPos, GetLoc().mZ);
	SetLoc(newLoc);

	mAngularVelocity += step * vec3_acAndRot.mZ;

	const float newRot = GetRot() + step * mAngularVelocity;
	SetRot(newRot);
}
#endif

#ifdef PATHFINDING
void Character::OnUpdatePathfinding(float step)
{
	int pfp = mSteering->getClosestPointOnPath();
	USVec2D newWaypoint(.0f, .0f);

	//m_01
	USVec2D A = getPathPoints().mPathPoints[pfp - 1];
	//if ((GetLoc() - A).Length() > 0.1f)
	//{
		USVec2D B = getPathPoints().mPathPoints[pfp];
		USVec2D AB(B - A);
		USVec2D AP(GetLoc() - A);
		newWaypoint = AB;
		newWaypoint.Scale(AP.Dot(AB));
		newWaypoint.Add(A);
	//}
	//else
	//{
		newWaypoint = getPathPoints().mPathPoints[pfp];
	//}
	mParams.targetPosition = newWaypoint;
	
	//m_02
	//float res1 = ((Bx - Ax) * posX) + ((By - Ay) * posY);
	//float res2 = posX^2 + posY^2
	//float res1 / sqrt(res2)

	//mParams.targetPosition = getPathPoints().mPathPoints[pfp];

	angle = getAngleFromVectors(USVec2D(GetLoc().mX, GetLoc().mY), USVec2D(GetLoc().mX + 10.0f, GetLoc().mY), USVec2D(GetLoc().mX, GetLoc().mY), USVec2D(mParams.targetPosition.mX, mParams.targetPosition.mY));
	USVec3D vec3_acAndRot = mSteering->getSteering(mParams.targetPosition, angle);

	USVec2D vec2_ac = USVec2D(vec3_acAndRot.mX, vec3_acAndRot.mY);

	mLinearVelocity.mX += step * vec2_ac.mX;
	mLinearVelocity.mY += step * vec2_ac.mY;

	const USVec2D newPos(GetLoc().mX + (step * mLinearVelocity.mX), GetLoc().mY + (step * mLinearVelocity.mY));
	const USVec3D newLoc(newPos, GetLoc().mZ);
	SetLoc(newLoc);

	mAngularVelocity += step * vec3_acAndRot.mZ;

	const float newRot = GetRot() + step * mAngularVelocity;
	SetRot(newRot);
}
#endif

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 0.0f);
	gfxDevice.SetPenWidth(55.0f);
	MOAIDraw::DrawPoint(mParams.targetPosition.mX, mParams.targetPosition.mY);
#ifndef NOTMOVEMENT
	mSteering->DrawDebug();
#endif 
}

// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ "setOwnerName",			_setOwnerName},
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

int Character::_setOwnerName(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	int ownerType = state.GetValue<int>(2, 0);
	self->SetOwnerName(ownerType);

	return 0;
}
