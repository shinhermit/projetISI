/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Build meshes by sampling a mathematical function z=f(x,y)
 *
 *
 */
#ifndef FUNCSURFACE_H
#define FUNCSURFACE_H

#include <sstream>

#include "triMesh.h"
#include "functionals/functionals.h"

namespace my{

/**
 * Build meshes by sampling a mathematical function z=f(x,y).
 * The mathematical function is represented by an instance of a class that extends my::Functional. That mathematical function is passed to the sampler throw the constructor.
 *
 */
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
    /**
      *Initializes the sampler
      */
    void _init(const Functional & f, const int & nbx, const int & nby,
               const float & minx, const float & maxx,
               const float & miny, const float & maxy);

    /**
      * Defines a general method of vertex insertion when sampling a function. This method is intended to be used by _functionalVertexInsertion.
      *@param f an instance of my::Functional that handles a mathematical calculus.
      *@param i sampling step for x (considering the function is z = f(x,y))
      *@param j sampling step for y (considering the function is z = f(x,y))
      */
    int _functionalVertexInsertion(const Functional & f, const int & i, const int & j);

    /**
      * Defines a strategy for triangles insertion when sampling a function.
      *@param f an instance of my::Functional that handles a mathematical calculus.
      */
    void _buildMesh(const Functional & f);

    /**
      * Fits the mesh in the box [-1,1]^3
      */
    void _fitMesh();

public:
    /**
      *Constructor.
      * @param nbx number of sampling step on the x coordinate
      * @param nby number of sampling step on the y coordinate
      * @param minx min value on x axis
      * @param maxx max value on x axis
      * @param miny min value on y axis
      * @param maxy max value on y axis
      *@param f an instance of my::Functional represents the mathematical function.
      */
    FuncSurface(int nbx, int nby, float minx, float maxx,
                float miny, float maxy, const Functional & f=my::FuncExpCos());
};

}

#endif // FUNCSURFACE_H
