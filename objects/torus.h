/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * A Torus
 *
 *
 */
#ifndef TORUS_H
#define TORUS_H

#include "parametricmesh.h"
#include "parametrics/toric.h"

namespace my{

class Torus : public ParametricMesh
{
private:
    float _pathRadius;
    float _tubeRadius;
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

    void _preTorus(const float & pathRadius, const float & tubeRadius, const int & nbSlices, const int & nbStacks);

public:
    Torus(const float & pathRadius=0.6, const float & tubeRadius=0.4, const int & nbSlices=20, const int & nbStacks=5);
};

}

#endif // TORUS_H
