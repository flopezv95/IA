#include <stdafx.h>
#include <tinyxml.h>
#include "params.h"

bool ReadParams(const char* filename, Params& params)
{
    TiXmlDocument doc(filename);
    if (!doc.LoadFile())
    {
        fprintf(stderr, "Couldn't read params from %s", filename);
        return false;
    }

    TiXmlHandle hDoc(&doc);

    TiXmlElement* pElem;
    pElem = hDoc.FirstChildElement().Element();
    if (!pElem)
    {
        fprintf(stderr, "Invalid format for %s", filename);
        return false;
    }

    TiXmlHandle hRoot(pElem);
    TiXmlHandle hParams = hRoot.FirstChildElement("params");

    TiXmlElement* paramElem = hParams.FirstChildElement("max_velocity").Element();
    if (paramElem)
        paramElem->Attribute("value", &params.max_velocity);

    paramElem = hParams.FirstChildElement("max_acceleration").Element();
    if (paramElem)
        paramElem->Attribute("value", &params.max_acceleration);

    paramElem = hParams.FirstChildElement("dest_radius").Element();
    if (paramElem)
        paramElem->Attribute("value", &params.dest_radius);

	paramElem = hParams.FirstChildElement("arrive_radius").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.arrive_radius);

	paramElem = hParams.FirstChildElement("targetPosition").Element();
	if (paramElem)
	{
		paramElem->Attribute("x", &params.targetPosition.mX);
		paramElem->Attribute("y", &params.targetPosition.mY);
	}


	paramElem = hParams.FirstChildElement("max_angular_velocity").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.max_angular_velocity);

	paramElem = hParams.FirstChildElement("max_angular_acceleration").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.max_angular_acceleration);

	paramElem = hParams.FirstChildElement("angular_dest_radius").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.angular_dest_radius);

	paramElem = hParams.FirstChildElement("angular_arrive_radius").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.angular_arrive_radius);

    return true;
}

bool ReadPathPoints(const char* filename, PathPoints& pathPoints)
{
	TiXmlDocument doc(filename);
	if (!doc.LoadFile())
	{
		fprintf(stderr, "Couldn't read params from %s", filename);
		return false;
	}

	TiXmlHandle hDoc(&doc);

	TiXmlElement* pElem;
	pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
	{
		fprintf(stderr, "Invalid format for %s", filename);
		return false;
	}

	TiXmlHandle hRoot(pElem);
	TiXmlHandle hParams = hRoot.FirstChildElement("points");

	TiXmlElement* paramElem = hParams.FirstChild().Element();
	for (paramElem; paramElem; paramElem = paramElem->NextSiblingElement())
	{
	    const char* paramName = paramElem->Value();
	    if (!strcmp(paramName, "point"))
	    {
			paramElem->Attribute("x", &pathPoints.mX);
			paramElem->Attribute("y", &pathPoints.mY);
			USVec2D v(pathPoints.mX, pathPoints.mY);
			pathPoints.mPathPoints.push_back(v);
	    }
	}

	return true;
}

bool ReadStateMachineParams(const char * filename, StateMach & params)
{
	TiXmlDocument doc(filename);
	if (!doc.LoadFile())
	{
		fprintf(stderr, "Couldn't read states from %s", filename);
		return false;
	}

	TiXmlHandle hDoc(&doc);

	TiXmlElement* pElem;
	pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
	{
		fprintf(stderr, "Invalid format for %s", filename);
		return false;
	}

	TiXmlHandle hRoot(pElem);

	TiXmlHandle hStates = hRoot.FirstChildElement("states");
	TiXmlElement* stateElem = hStates.FirstChild().Element();
	int childIdx = 0;
	for (stateElem; stateElem; stateElem = stateElem->NextSiblingElement())
	{
		const char* StateParamName = stateElem->Value();
		if (!strcmp(StateParamName, "state"))
		{
			StateStruct newState;
			newState.StateName = stateElem->Attribute("value");

			//TiXmlHandle hState = hStates.FirstChildElement("state");
			TiXmlHandle hState = hStates.ChildElement(childIdx);
			++childIdx;
			TiXmlElement* subStateElem = hState.FirstChild().Element();
			for (subStateElem; subStateElem; subStateElem = subStateElem->NextSiblingElement())
			{
				const char* SubStateParamName = subStateElem->Value();
				
				if (!strcmp(SubStateParamName, "action"))
				{	
					newState.Action = subStateElem->Attribute("value");
				}
				else if (!strcmp(SubStateParamName, "transitions"))
				{
					newState.Transitions.insert(std::pair<std::string, std::string>(subStateElem->Attribute("con"), subStateElem->Attribute("st")));
				}
			}
			params.States.push_back(newState);
		}
	}

	return true;
}

bool ReadBTParams(const char * filename, BTStruct & params)
{
	TiXmlDocument doc(filename);
	if (!doc.LoadFile())
	{
		fprintf(stderr, "Couldn't read states from %s", filename);
		return false;
	}

	TiXmlHandle hDoc(&doc);

	TiXmlElement* pElem;
	pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
	{
		fprintf(stderr, "Invalid format for %s", filename);
		return false;
	}

	TiXmlHandle hRoot(pElem);

	TiXmlHandle hBt = hRoot.FirstChildElement("selector");
	TiXmlElement* nodeElem = hBt.FirstChild().Element();
	int childIdx = 0;
	for (nodeElem; nodeElem; nodeElem = nodeElem->NextSiblingElement())
	{
		const char* StateParamName = nodeElem->Value();
		if (!strcmp(StateParamName, "group"))
		{
			NodeStruct newNode;
			newNode.Type = nodeElem->Attribute("value");

			TiXmlHandle hNode = hBt.ChildElement(childIdx);
			++childIdx;
			TiXmlElement* subNodeElem = hNode.FirstChild().Element();
			for (subNodeElem; subNodeElem; subNodeElem = subNodeElem->NextSiblingElement())
			{
				const char* SubStateParamName = subNodeElem->Value();
				NodeStruct SubNewNode;
				SubNewNode.Type = subNodeElem->Attribute("value");
				newNode.ChildNodes.push_back(SubNewNode);
			}
			params.Nodes.push_back(newNode);
		}
	}
	return true;
}
