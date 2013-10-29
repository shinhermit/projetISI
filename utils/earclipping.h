#ifndef EARCLIPPING_H
#define EARCLIPPING_H

#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <iostream>

#include "ipolygontriangulator.h"
#include "iMesh.h"
#include "geometry.h"

namespace my{

class EarClipping : public IPolygonTriangulator
{
private:
    const my::IPolygon * _poly;
    my::Orientation _orientation;
    std::vector<my::Triangle> * _triangulation;
    std::vector<int> _currentPoly;
    std::list<int> _convexVertices;
    std::list<int> _reflexVertices;
    std::deque<int> _earVertices;

    int _cyclicPrev(const int & vertex)const;
    int _cyclicNext(const int & vertex)const;
    bool _convexVertex(const int & vertex)const;
    bool _insideTriangle(const my::Point & A, const my::Point & B, const my::Point & C, const my::Point & M)const;
    bool _earVertex(const int & vertexRef)const;
    void _buildConvexityLists();
    void _addTriangle(const int & earVertex);
    void _checkConvexityChanges(const int & vertex);
    void _renumberLists(const int & earVertex);
    void _updateLists(const int & earVertex);

    void _preProcess(const my::IPolygon & poly) throw(std::invalid_argument);
    void _clearLists();
    void _init(const my::IPolygon & poly, std::vector<my::Triangle> & triangulation);


public:
    EarClipping();
    void process(const my::IPolygon & poly, std::vector<my::Triangle> & triangulation);
};

}

#endif // EARCLIPPING_H
