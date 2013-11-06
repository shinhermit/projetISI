#include "func_surface.h"

void my::FuncSurface::_preFuncSurface(const int & nbx, const int & nby)
{
    std::ostringstream oss;
    bool invalid = false;

    if(nbx < 0){
        oss << "FuncSurface::_preFuncSurfac: number of x sampling steps can not be negative" << std::endl
            << "\t given value is " << nbx << std::endl;
        invalid = true;
    }

    if(nby < 0){
        oss << "FuncSurface::_preFuncSurfac: number of y sampling steps can not be negative" << std::endl
            << "\t given value is " << nby << std::endl;
        invalid = true;
    }

    if(invalid)
        throw std::invalid_argument(oss.str());
}

void my::FuncSurface::_init(const Functional & f, const int & nbx, const int & nby, const float & minx, const float & maxx, const float & miny, const float & maxy)
{
    _xmin = minx;
    _xmax = maxx;
    _ymin = miny;
    _ymax = maxy;
    _nbx = nbx;
    _nby = nby;

    _zmin = f(_xmin, _ymin);
    _zmax = _zmin;

    _xStep = (_xmax - _xmin)/(_nbx-1);
    _yStep = (_ymax - _ymin)/(_nby-1);
}

int my::FuncSurface::_functionalVertexInsertion(const Functional & f, const int & i, const int & j)
{
    float x, y, z;

    x = _xmin + i*_xStep;
    y = _ymin + j*_yStep;
    z = f(x,y);
    addVertex(x,y,z);

    if(z < _zmin)
        _zmin = z;
    else if(z > _zmax)
        _zmax = z;

    return sizeV()-1;
}

void my::FuncSurface::_buildMesh(const Functional & f)
{
    int A, B, C, D;

    for(int i=0; i < _nbx-1; ++i){
        for(int j=0; j < _nby-1; ++j){
            A = _functionalVertexInsertion(f,i,j);
            B = _functionalVertexInsertion(f,i+1,j);
            C = _functionalVertexInsertion(f,i+1,j+1);
            D = _functionalVertexInsertion(f,i,j+1);

            addTriangle(A,B,C);
            addTriangle(A,C,D);
        }
    }
}

void my::FuncSurface::_fitMesh()
{
    my::Vertex translate(-(_xmax + _xmin)/2.,
                         -(_ymax + _ymin)/2.,
                         -(_zmax + _zmin)/2. );
    my::Vertex scale(1./(_xmax - (_xmax + _xmin)/2.),
                     1./(_ymax - (_ymax + _ymin)/2.),
                     1./(_zmax - (_zmax + _zmin)/2.));

    for(int i=0; i< _vertices.size(); ++i){
        _vertices[i] = (_vertices[i]+translate)*scale;
    }

    computeBoundingBox();
}

my::FuncSurface::FuncSurface(int nbx, int nby,
                         float minx, float maxx, float miny, float maxy, const my::Functional & f)
    :TriMesh("FuncSurface")
{
    _preFuncSurface(nbx, nby);
    _init(f, nbx, nby, minx, maxx, miny, maxy);

    _buildMesh(f);
    _fitMesh();

    computeNormalsT();
    computeNormalsV();
}
