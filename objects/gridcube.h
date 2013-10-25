#ifndef GRIDCUBE_H
#define GRIDCUBE_H

#include "parametricmesh.h"
#include "grid.h"

namespace my
{

class GridCube : public ParametricMesh
{
private:
    float _height;
    int _nbXdiv;
    int _nbYdiv;
    int _nbZdiv;
    my::Point _center;

    void _preGridCube(const float & height, const int & nbXdiv, const int & nbYdiv, const int & nbZdiv);
public:
    GridCube(const float & height=2., const int & nbXdiv=1., const int & nbYdiv=1., const int & nbZdiv=1., const my::Point & center=my::Point(0,0,0));
};

}

#endif // GRIDCUBE_H
