#ifndef SPHERE_H
#define SPHERE_H

#include "parametricmesh.h"
#include "parametrics/spheric.h"

namespace my{

class Sphere : public ParametricMesh
{
private:
    float _radius;
    float _nbSlices;
    float _nbStacks;

    my::Parameters _sampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument);
    int _indiceOfSampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument);

    void _preSphere(const float & radius, const int & nbSlices, const int & nbStacks) throw(std::invalid_argument);
public:
    Sphere(const float & radius=1., const int & nbSlices=2, const int & nbStacks=2);
};

}

#endif // SPHERE_H
