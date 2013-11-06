/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Parametric equation of a Sphere
 *
 *
 */
#ifndef SPHERIC_H
#define SPHERIC_H

#include "parametric.h"

namespace my{

/**
  *Represents the parametric equation of a sphere.
  * Implements my::Parametric
  */
class Spheric : public Parametric
{
private:
    float _radius;

    void _preSpheric(const float &radius);
    void _preOperatorCall(const float& polar, const float& azimutal);

public:
    /**
      *Constructor
      *@param radius radius of the sphere
      */
    Spheric(const float &radius=1.);

    /**
      *@see my::Paramtric::operator()
      */
    Point operator()(const float& polar, const float& azimutal) throw(std::invalid_argument);
};

}

#endif // SPHERIC_H
