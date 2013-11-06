/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Provides partial implementation of interface IPolygon
 *
 *
 */
#ifndef ABSTRACTPOLYGON_H
#define ABSTRACTPOLYGON_H

#include <stdexcept>
#include <sstream>
#include <string>

#include "ipolygon.h"

namespace my{

/**
  * This abstract factors all the behaviours that can be deduced from the part that remain undetermined.
  * The undeterminated behaviours will be given be subclasses of AbstractPolygon.
  * Once these behaviours are given, the one defined by AbstractPolygon will then be automatically fully fonctionnal.
  */
class AbstractPolygon : public IPolygon
{
private:
    void _preIndice(const int & i, const std::string & methodName)const throw(std::out_of_range);
    void _prePolygon(const std::string & method)const throw(std::runtime_error);

public:
    /**
      *@see my::IPolygon::edgeVector
      */
    virtual my::Vector edgeVector(const int & i)const throw(std::out_of_range);

    /**
      *@see my::IPolygon::next
      */
    virtual int next(const int & vertex) const throw(std::out_of_range);

    /**
      *@see my::IPolygon::prev
      */
    virtual int prev(const int & vertex) const throw(std::out_of_range);

    /**
      *@see my::IPolygon::basePlane
      */
    virtual my::Planar basePlane()const;

    /**
      *@see my::IPolygon::basePlaneExpression
      */
    virtual my::PlanarExpression basePlaneExpression()const;

    /**
      *@see my::IPolygon::signedArea
      */
    virtual float signedArea()const;

    /**
      *@see my::IPolygon::area
      */
    virtual float area()const;

    /**
      *@see my::IPolygon::orientation
      */
    virtual my::Orientation orientation()const;


    /**
      *@see my::IPolygon::circumference
      */
    virtual float circumference()const;


    /**
      *@see my::IPolygon::toString
      */
    virtual std::string toString()const;
};

}
#endif // ABSTRACTPOLYGON_H
