/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Base class for representing parametric equations.
 *
 *
 */
#ifndef PARAMETRIC_H
#define PARAMETRIC_H

#include <stdexcept>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtx/constants.hpp>
#include "../my_types.h"
#include "utils/constant.h"

namespace my{

/**
  *Represents the parametric equation of a 3D surface.
  * Every 3D surface can be parametrized with 3 parameter, that we will denote s and t.
  * Given a couple of values for (s,t), an instance of a subclass of my::Parametric provides tha x,y and z coordinates of a point of the surface.
  * We treat in this prject on regular surfaces.
  */
class Parametric
{
public:
    Parametric();
    virtual ~Parametric();

    /**
      * Given a couple of values for (s,t), an instance of a subclass of my::Parametric provides tha x,y and z coordinates of a point of the surface.
      *@param s value for the first parameter of the parametric equation
      *@param t value for the second parameter of the parametric equation
      */
    virtual Point operator()(const float & s, const float & t) throw(std::invalid_argument) =0;
};

}

#endif // PARAMETRIC_H
