#ifndef ABSTRACTPOLYGON_H
#define ABSTRACTPOLYGON_H

#include <stdexcept>
#include <sstream>
#include <string>

#include "ipolygon.h"

namespace my{

class AbstractPolygon : public IPolygon
{
private:
    void _preIndice(const int & i, const std::string & methodName)const throw(std::out_of_range);
    void _prePolygon(const std::string & method)const throw(std::runtime_error);

public:
    virtual my::Vector edgeVector(const int & i)const throw(std::out_of_range);
    virtual int next(const int & vertex) const throw(std::out_of_range);
    virtual int prev(const int & vertex) const throw(std::out_of_range);

    virtual my::Planar basePlane()const;
    virtual my::PlanarExpression basePlaneExpression()const;

    virtual float signedArea()const;
    virtual float area()const;
    virtual my::Orientation orientation()const;

    virtual float circumference()const;

    virtual std::string toString()const;
};

}
#endif // ABSTRACTPOLYGON_H
