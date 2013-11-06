/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * An opened Cylinder
 *
 *
 */
#ifndef CYLINDRICMESH_H
#define CYLINDRICMESH_H

#include "parametricmesh.h"
#include "parametrics/cylindric.h"

namespace my{

class CylindricMesh: public ParametricMesh
{
private:
    float _height;
    float _radius;
    int _nbSlices;
    int _nbStacks;

    /**
      *@see my::ParametricMesh::_sampled
      */
    my::Parameters _sampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument);
    /**
      *@see my::ParametricMesh::_indiceOfSampled
      */
    int _indiceOfSampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument);

    void _preCylindricMesh(const float & height, const float & radius, const int & nbSlices, const int & nbStacks);

public:
    CylindricMesh(const float & height=2., const float & radius=1., const int & nbSlices=10, const int & nbStacks=5);
};

}

#endif // CYLINDRICMESH_H
