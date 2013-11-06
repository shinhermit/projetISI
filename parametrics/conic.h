/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Parametric equation of a cone.
 *
 *
 */
#ifndef CONIC_H
#define CONIC_H

#include "parametric.h"

namespace my{


/**
  *Represents the parametric equation of a cone.
  * Implements my::Parametric
  */
class Conic: public Parametric
{
private:
    float _aperture;
    my::Point _center;

    void _preInit(const float & aperture) throw(std::invalid_argument);
    void _init(const float & aperture);

public:
    /**
      *Constructor
      *@param position of the center of the cone
      *@param aperture angle at the tip of the cone
      */
    Conic(const my::Point & center, const float & aperture=26.5) throw(std::invalid_argument);

    /**
      *Constructor
      *@param aperture angle at the tip of the cone
      */
    Conic(const float & aperture=26.5) throw(std::invalid_argument);

    /**
      *@see my::Paramtric::operator()
      */
    Point operator()(const float& z, const float& azimut) throw(std::invalid_argument);
};

}
#endif // CONIC_H
