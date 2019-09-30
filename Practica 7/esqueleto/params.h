#ifndef __PARAMS_H__
#define __PARAMS_H__
#include <iostream>
#include <vector>
#include <map>

struct StateStruct
{
	std::string StateName;
	std::string Action;
	std::map<std::string, std::string> Transitions;
};
struct NodeStruct
{
	std::string Type;
	std::vector<NodeStruct> ChildNodes;
};
struct BTStruct
{
	std::vector<NodeStruct> Nodes;
};
struct StateMach
{
	std::vector<StateStruct> States;
};

struct Params
{
    USVec2D targetPosition = USVec2D(-50.0f,-200.0f);
    float max_velocity = 40.0f;
    float max_acceleration = 40.0f;
    float dest_radius = 40.0f;
	float arrive_radius = 80.0f;

	float max_angular_velocity = 1.0f;
	float max_angular_acceleration = 1.0f;
	float angular_dest_radius = 2.0f;
	float angular_arrive_radius = 30.0f;
	
};

struct PathPoints
{
	float mX;
	float mY;
	std::vector<USVec2D> mPathPoints;
};

bool ReadParams(const char* filename, Params& params);
bool ReadPathPoints(const char* filename, PathPoints& pathPoints);
bool ReadStateMachineParams(const char* filename, StateMach& params);
bool ReadBTParams(const char* filename, BTStruct& params);

#endif