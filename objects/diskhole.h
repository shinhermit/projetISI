#ifndef DISKHOLE_H
#define DISKHOLE_H

#include "parametricmesh.h"
#include "parametrics/circular.h"

namespace my{

class DiskHole : public ParametricMesh
{
private:
    float _bigRadius;
    float _smallRadius;
    int _nbSlices;
    int _nbCirc;

    my::Parameters _sampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument);
    int _indiceOfSampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument);

    void _preDiskHole(const float & bigRadius, const float & smallRadius, const int & nbSlices, const int & nbCirc) throw(std::invalid_argument);

public:
    DiskHole(const float & bigRadius=1., const float & smallRadius=0.5, const int & nbSlices=10, const int & nbCirc=1);
};

}

#endif // DISKHOLE_H
