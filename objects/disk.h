#ifndef DISK_H
#define DISK_H

#include "parametricmesh.h"
#include "parametrics/circular.h"

namespace my{

class Disk: public ParametricMesh
{
private:
    float _radius;
    int _nbSlices;
    int _nbCirc;

    float _angleStep;
    float _radiusStep;
    int _nbVertexPerCircle;

    my::Parameters _sampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument);
    int _indiceOfSampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument);

    void _preDisk(const float & radius, const int & nbSlices, const int & nbCirc) throw(std::invalid_argument);

public:
    Disk(const float & radius=1., const int & nbSlices=10, const int & nbCirc=1, const my::Point & center=my::Point(0,0,0));
};

}

#endif // DISK_H
