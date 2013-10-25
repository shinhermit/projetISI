#ifndef FUNCSURFACE_H
#define FUNCSURFACE_H

#include <sstream>

#include "triMesh.h"
#include "functionals/functionals.h"

namespace my{

class FuncSurface : public TriMesh
{
private:
    float _xmin;
    float _xmax;
    float _ymin;
    float _ymax;
    float _zmin;
    float _zmax;
    float _xStep;
    float _yStep;
    int _nbx;
    int _nby;

    void _preFuncSurface(const int & nbx, const int & nby);
    void _init(const Functional & f, const int & nbx, const int & nby,
               const float & minx, const float & maxx,
               const float & miny, const float & maxy);

    int _functionalVertexInsertion(const Functional & f, const int & i, const int & j);

    void _buildMesh(const Functional & f);

    void _fitMesh();

public:

    FuncSurface(int nbx, int nby, float minx, float maxx,
                float miny, float maxy, const Functional & f=my::FuncExpCos());
};

}

#endif // FUNCSURFACE_H
