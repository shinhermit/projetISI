/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Parametric equation of a circle
 *
 *
 */
#ifndef CIRCULAR_H
#define CIRCULAR_H

#include <iostream>
#include <sstream>

#include "parametric.h"

namespace my{

/**
  *Represents the parametric equation of a circle.
  * Implements my::Parametric
  */
class Circular: public Parametric
{
private:
    float _radius;
    my::Point _center;

    void _preCircular(const float & radius);
    void _preOperatorCall(const float & distance, const float & azimut) throw(std::invalid_argument);

public:
    /**
      *Constructor
      *@param radius radisu of the circle
      *@param center center point of the circle.
      */
    Circular(const float & radius=1., const my::Point & center=my::Point(0,0,0));

    /**
      *@see my::Paramtric::operator()
      */
    Point operator()(const float & distance, const float & azimut) throw(std::invalid_argument);
};

}

#endif // CIRCULAR_H
