/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Parametric equation of a cylinder
 *
 *
 */
#ifndef CYLINDRIC_H
#define CYLINDRIC_H

#include "parametric.h"

namespace my{

/**
  *Represents the parametric equation of a cylinder.
  * Implements my::Parametric
  */
class Cylindric : public Parametric
{
private:
    float _radius;
    my::Point _center;

    void _preCylindric(const float & radius);
    void _preOperatorCall(const float & alpha);

public:
    /**
      *Constructor
      *@param radius radius of the base circle of the cylinder
      *@param center center point of the cylinder
      */
    Cylindric(const float & radius=1., const my::Point & center=my::Point(0,0,0));

    /**
      *@see my::Paramtric::operator()
      */
    Point operator()(const float & z, const float & alpha) throw(std::invalid_argument);
};

}
#endif // CYLINDRIC_H
