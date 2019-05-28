#ifndef __PARAMS_H__
#define __PARAMS_H__

#include <vector>


struct Polygons
{
	std::vector<USVec2D> myVertex;
};


struct GeometryNavMesh
{
	std::vector<Polygons> myPathPoints;
};

bool ReadNavMesh(const char* filename, GeometryNavMesh& params);


#endif