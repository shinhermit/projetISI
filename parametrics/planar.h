/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Parametric equation of a Plane
 *
 *
 */
#ifndef PLANAR_H
#define PLANAR_H

#include "parametric.h"

namespace my{

/**
  *Represents the parametric equation of a plane.
  * Implements my::Parametric
  */
class Planar : public Parametric
{
private:
    my::Point _A;
    my::Vector _u;
    my::Vector _v;

public:
    /**
      *Constructor
      *@param A a point of the plane (that will be the origin of the local landmark)
      *@param u a leading vector of the plane
      *@param v another leading vector of the plane, non-colinear to u
      */
    Planar(const my::Point & A, const my::Vector & u, const my::Vector & v);

    /**
      *@see my::Paramtric::operator()
      */
    virtual Point operator()(const float&, const float&) throw(std::invalid_argument);
};

}

#endif // PLANAR_H
