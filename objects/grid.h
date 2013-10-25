#ifndef GRID_H
#define GRID_H

#include "parametricmesh.h"
#include "parametrics/planar.h"

namespace my
{

class Grid : public ParametricMesh
{
private:
    my::Point _A;
    my::Vector _u;
    my::Vector _v;
    float _width;
    float _length;
    int _nbSlices;
    int _nbStacks;

    my::Parameters _sampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument);
    int _indiceOfSampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument);

    void _preGrid(const float & width, const float & length, const int & nbSdiv, const int & nbTdiv);

public:
    Grid(const my::Point & A=my::Point(0,0,0), const my::Vector & u=my::Vector(1,0,0), const my::Vector & v=my::Point(0,0,1), const float & width=2., const float & length=2., const int & nbSdiv=1, const int & nbTdiv=1);
};

}

#endif // GRID_H
