/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * A closed Cone
 *
 *
 */
#ifndef CONE_H
#define CONE_H

#include "parametricmesh.h"
#include "conicmesh.h"
#include "disk.h"

namespace my{

class Cone : public ParametricMesh
{
private:

    void _preCone(const float & height, const float & aperture, const int & nbSlices, const int & nbStacks, const int &nbCirc) throw(std::invalid_argument);

public:
    Cone(const float & height=1., const float & aperture=26.5, const int & nbSlices=10, const int & nbStacks=5, const int & nbCirc=1);
};

}

#endif // CONE_H
