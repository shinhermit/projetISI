#ifndef IPOLYGON_H
#define IPOLYGON_H

#include "my_types.h"
#include "parametrics/planar.h"
#include "planarexpression.h"

namespace my{

class IPolygon
{
public:
    // add method must preserve the planar property of the polygon
    virtual void addVertex(const my::Vertex & vertex)=0;
    virtual void addVertex(const float & x, const float & y, const float & z)=0;

    virtual void removeVertex(const int & i) throw(std::out_of_range)=0;
    virtual void clear()=0;

    virtual int size()const=0;
    virtual my::Vertex vertex(const int & i)const throw(std::out_of_range)=0;
    virtual my::Vector edgeVector(const int & i)const throw(std::out_of_range)=0;
    virtual int next(const int & i) const throw(std::out_of_range)=0;
    virtual int prev(const int & i) const throw(std::out_of_range)=0;

    virtual my::Planar basePlane()const=0;
    virtual my::PlanarExpression basePlaneExpression()const=0;

    virtual float signedArea()const=0;
    virtual float area()const=0;
    virtual my::Orientation orientation()const=0;

    virtual float circumference()const=0;

    virtual std::string toString()const=0;
};

}
#endif // IPOLYGON_H
