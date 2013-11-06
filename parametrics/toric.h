/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Parametric equation of a Tore
 *
 *
 */
#ifndef TORIC_H
#define TORIC_H

#include "parametric.h"

namespace my{

/**
  *Represents the parametric equation of a tore.
  * Implements my::Parametric
  */
class Toric : public Parametric
{
private:
    float _pathRadius;
    float _tubeRadius;

    void _preToric(const float & pathRadius, const float & tubeRadius);
    void _preOperatorCall(const float& pathAngle, const float& tubeAngle);

public:
    /**
      *Constructor
      *@param pathRadius radius of the leading path
      *@param tubeRadius radius of the ben tube
      */
    Toric(const float & pathRadius=0.6, const float & tubeRadius=0.4);

    /**
      *@see my::Paramtric::operator()
      */
    Point operator()(const float& pathAngle, const float& tubeAngle) throw(std::invalid_argument);
};

}
#endif // TORIC_H
