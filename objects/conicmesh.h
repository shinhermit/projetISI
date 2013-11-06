/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * An opened Cone
 *
 *
 */
#ifndef CONICMESH_H
#define CONICMESH_H

#include "parametricmesh.h"
#include "parametrics/conic.h"

namespace my{

class ConicMesh : public ParametricMesh
{
private:
    float _height;
    float _aperture;
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

    void _preConicMesh(const float & height, const float & aperture, const int & nbSlices, const int & nbStacks) throw(std::invalid_argument);
public:
    ConicMesh(const float & height=1., const float & aperture=26.5, const int & nbSlices=10, const int & nbStacks=5);
};

}

#endif // CONICMESH_H
