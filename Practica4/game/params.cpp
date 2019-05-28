#include <stdafx.h>
#include <tinyxml.h>
#include "params.h"

bool ReadNavMesh(const char* filename, GeometryNavMesh& params)
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
	TiXmlHandle hParams = hRoot.FirstChildElement("polygons");
	TiXmlHandle hParams2 = hParams.FirstChildElement("polygon");
	TiXmlElement* paramElem = hParams2.Element();
	for (paramElem; paramElem; paramElem = paramElem->NextSiblingElement())
	{
		TiXmlElement* paramElem2 = paramElem->FirstChild()->ToElement();
		Polygons myPolygon;
		for (paramElem2; paramElem2; paramElem2 = paramElem2->NextSiblingElement())
		{
			const char* paramName = paramElem2->Value();
			if (!strcmp(paramName, "point"))
			{
				float positionX;
				float positionY;
				paramElem2->Attribute("x", &positionX);
				paramElem2->Attribute("y", &positionY);
				USVec2D pointPosition(positionX, positionY);
				myPolygon.myVertex.push_back(pointPosition);

			}
		}
		params.myPathPoints.push_back(myPolygon);
	}

		return true;
}
