#ifndef CYLINDER_H
#define CYLINDER_H

#include "parametricmesh.h"
#include "cylindricmesh.h"
#include "disk.h"

namespace my{

class Cylinder: public ParametricMesh
{
private:

    void _preCylinder(const float & height, const float & radius, const int & nbSlices, const int & nbStacks, const int & nbCirc);

public:
    Cylinder(const float & height=2., const float & radius=1., const int & nbSlices=10, const int & nbStacks=5, const int & nbCirc=1);
};

}

#endif // CYLINDER_H
